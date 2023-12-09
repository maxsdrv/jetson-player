#include <QThread>
#include <QNetworkAccessManager>
#include <QMutex>
#include <QNetworkReply>
#include <QTimer>
#include <QJsonDocument>

#include "playerworker.h"

PlayerWorker::PlayerWorker(QObject *parent)
    : QObject{parent}, _networkManager{new QNetworkAccessManager(this)},
      _connectionTimer{new QTimer(this)}
{

    connect(_networkManager, &QNetworkAccessManager::finished, this, &PlayerWorker::networkReply);
    connect(this, &PlayerWorker::newRequestEnqueue, this, &PlayerWorker::processQueue);

    moveToThread(&_thread);
    _thread.start();
}

PlayerWorker::~PlayerWorker()
{
    _thread.quit();
    _thread.wait();

    qDebug() << __func__;
}

void PlayerWorker::enqueueRequest(const HttpRequestData &request)
{
    {
        QMutexLocker locker(&_queueMutex);
        _requestQueue.enqueue(request);
    }

    emit newRequestEnqueue();
}

void PlayerWorker::setupTimers()
{
    connect(_connectionTimer, &QTimer::timeout, this, &PlayerWorker::checkConnection);
    _connectionTimer->start(10000);
}

void PlayerWorker::setUrl(QString url)
{
    if (_serverUrl != url && !url.isEmpty())
        _serverUrl = url;
}

void PlayerWorker::sendRequest(const HttpRequestData& requestData)
{
    QString fullUrl = _serverUrl + requestData.endpoint;
    QNetworkRequest request((QUrl(fullUrl)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    switch (requestData.requestType) {
    case HttpRequestData::RequestType::GET:
        _networkManager->get(request);
        break;
    case HttpRequestData::RequestType::POST:
        QJsonDocument doc(requestData.data);
        QByteArray byteData = doc.toJson();
        _networkManager->post(request, byteData);
        break;
    }
}

void PlayerWorker::checkConnection()
{
    HttpRequestData request;
    request.endpoint = "/heartbeat";
    request.requestType = HttpRequestData::RequestType::GET;
    enqueueRequest(request);

}

void PlayerWorker::networkReply(QNetworkReply* reply)
{
    if (reply->error()) {
        qDebug() << __func__ << "Error: " << reply->errorString();

        emit responseReceived("Error: " + reply->errorString());
        emit connectionLost();
    }

    else {
        QByteArray response = reply->readAll();
        qDebug() << __func__ << "Server Response: " << QString(response);

        emit responseReceived("Server Response: " + QString(response));
        emit connectionEstablished();
        _connectionTimer->stop();
    }


    reply->deleteLater();
}

void PlayerWorker::processQueue()
{
    HttpRequestData request;

    {
        QMutexLocker locker(&_queueMutex);

        if (_requestQueue.isEmpty())
            return;
        request = _requestQueue.dequeue();
    }

    sendRequest(request);
}






