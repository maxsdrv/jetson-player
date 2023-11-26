#include <QThread>
#include <QNetworkAccessManager>
#include <QMutex>
#include <QNetworkReply>

#include "playerworker.h"

PlayerWorker::PlayerWorker(QObject *parent)
    : QObject{parent}, _networkManager{new QNetworkAccessManager(this)}
{
    connect(_networkManager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) {
        if (reply->error()) {
            emit responseReceived("Error: " + reply->errorString());
        } else {
            QByteArray response = reply->readAll();
            emit responseReceived("Server Response: " + QString(response));
        }

        reply->deleteLater();
    });

    moveToThread(&_thread);
    _thread.start();
}

PlayerWorker::~PlayerWorker()
{
    _thread.quit();
    _thread.wait();
}

void PlayerWorker::enqueueRequest(const QString &request)
{
    QMutexLocker locker(&_queueMutex);
    _requestQueue.enqueue(request);
}

void PlayerWorker::sendRequest(const QString &request)
{

}

void PlayerWorker::checkConnection()
{

}
