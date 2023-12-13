#include <QThread>
#include <QMutex>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>

#include "playerworker.h"
#include "playerreceiver.h"
#include "playersender.h"

PlayerWorker::PlayerWorker(QObject *parent)
    : QObject{parent},
      _networkManager{new QNetworkAccessManager(this)},
      _playerReceiver{new PlayerReceiver{this}},
      _playerSender{new PlayerSender{_networkManager, this}},
      _connectionTimer{new QTimer(this)}
{
    senderConnections();
    receiverConnecions();

    moveToThread(&_thread);
    _thread.start();
}

PlayerWorker::~PlayerWorker()
{
    _thread.quit();
    _thread.wait();

    qDebug() << __func__;
}

void PlayerWorker::setupTimers()
{
    connect(_connectionTimer, &QTimer::timeout, this, &PlayerWorker::checkConnection);
    _connectionTimer->start(10000);
}

void PlayerWorker::connectionTimerStop()
{
    _connectionTimer->stop();
}

void PlayerWorker::setUrl(QString url)
{
    if (_serverUrl != url && !url.isEmpty())
        _serverUrl = url;

    emit urlUpdated(_serverUrl);
}


void PlayerWorker::senderConnections()
{
    connect(this, &PlayerWorker::enqueuePostRequest, _playerSender, &PlayerSender::preparePostRequest);

    connect(this, &PlayerWorker::enqueueGetRequest, _playerSender, &PlayerSender::prepareGetRequest);

    connect(this, &PlayerWorker::urlUpdated, _playerSender, &PlayerSender::setUrl);

}

void PlayerWorker::receiverConnecions()
{
    connect(_networkManager, &QNetworkAccessManager::finished, _playerReceiver, &PlayerReceiver::networkReply);
    connect(_playerReceiver, &PlayerReceiver::badRequest, this, &PlayerWorker::processingErrors);
    connect(_playerReceiver, &PlayerReceiver::responseReceived, this, &PlayerWorker::processingResponses);
}

void PlayerWorker::checkConnection()
{
    /*QJsonObject data;
    Runner message{"heartbeat", data};
    QByteArray messageData = message.toByteArray();*/
    emit enqueueGetRequest(messageTypes[MessageType::HEARTBEAT]);
}

void PlayerWorker::play()
{
    emit enqueueGetRequest(messageTypes[MessageType::PLAY]);
}

void PlayerWorker::stop()
{

}

void PlayerWorker::processingErrors(QString error)
{
    qDebug() << "Error: " << error;
}

void PlayerWorker::processingResponses(QString response, QString message)
{
    qDebug() << "Response: " << response << " " << message;
    connectionTimerStop();
}







