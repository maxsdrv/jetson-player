#include <QDebug>

#include "playersender.h"

PlayerSender::PlayerSender(QNetworkAccessManager *netManager, QObject* parent) : QObject{parent},
    _networkManager{netManager}
{
    connect(this, &PlayerSender::newRequestEnqueue, this, &PlayerSender::processQueue);

}

PlayerSender::~PlayerSender()
{
    qDebug() << __func__;
}

void PlayerSender::sendData(QString endpoint)
{
    HttpRequestData request {endpoint, HttpRequestData::RequestType::GET, QByteArray{}};

    enqueueRequest(request);
}

void PlayerSender::sendData(QString endpoint, const QByteArray &data)
{
    HttpRequestData request {endpoint, HttpRequestData::RequestType::POST, data};

    enqueueRequest(request);
}

void PlayerSender::setUrl(QString url)
{
    if (_serverUrl != url && !url.isEmpty())
        _serverUrl = url;
}

HttpRequestData PlayerSender::dequeueRequest()
{
    {
        QMutexLocker locker(&_queueMutex);
        if (_requestQueue.isEmpty())
            return HttpRequestData{};
    }

    return _requestQueue.dequeue();

}

void PlayerSender::enqueueRequest(const HttpRequestData &requestData)
{
    {
        QMutexLocker locker(&_queueMutex);
        _requestQueue.enqueue(requestData);
    }

    emit newRequestEnqueue();
}

void PlayerSender::processQueue()
{
    HttpRequestData request{};
    {
        QMutexLocker locker(&_queueMutex);

        if (_requestQueue.isEmpty())
            return;
        request = _requestQueue.dequeue();
    }

    sendRequest(request);

}

void PlayerSender::sendRequest(const HttpRequestData &requestData)
{
    QString fullUrl = _serverUrl + requestData.endpoint;
    QNetworkRequest request((QUrl(fullUrl)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (requestData.requestType == HttpRequestData::RequestType::POST) {
        _networkManager->post(request, requestData.data);
    }
    else if (requestData.requestType == HttpRequestData::RequestType::GET) {
        _networkManager->get(request);
    }
    else {
        qWarning() << "Bad Request Type!";
    }
}








