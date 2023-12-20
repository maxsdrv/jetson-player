#include <QThread>
#include <QMutex>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>

#include "playerworker.h"
#include "playerreceiver.h"
#include "playersender.h"

PlayerWorker::PlayerWorker()
    :
      _networkManager{new QNetworkAccessManager()},
      _playerReceiver{new PlayerReceiver()},
      _playerSender{new PlayerSender{_networkManager.get(), nullptr}}
{

    senderConnections();
    receiverConnecions();
}

PlayerWorker::~PlayerWorker()
{
    qDebug() << __func__;
}

void PlayerWorker::setUrl(QString url)
{
    if (_serverUrl != url && !url.isEmpty())
        _serverUrl = url;

    emit urlUpdated(_serverUrl);
}


void PlayerWorker::senderConnections()
{
    connect(this, &PlayerWorker::enqueuePostRequest, _playerSender.get(), &PlayerSender::preparePostRequest);
    connect(this, &PlayerWorker::enqueueGetRequest, _playerSender.get(), &PlayerSender::prepareGetRequest);
    connect(this, &PlayerWorker::urlUpdated, _playerSender.get(), &PlayerSender::setUrl);
}

void PlayerWorker::receiverConnecions()
{
    connect(_networkManager.get(), &QNetworkAccessManager::finished, _playerReceiver.get(), &PlayerReceiver::networkReply);
    connect(_playerReceiver.get(), &PlayerReceiver::badRequest, this, &PlayerWorker::processingErrors);
    connect(_playerReceiver.get(), &PlayerReceiver::responseReceived, this, &PlayerWorker::processingResponses);
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
    emit enqueueGetRequest(messageTypes[MessageType::STOP]);
}

void PlayerWorker::pause()
{
    emit enqueueGetRequest(messageTypes[MessageType::PAUSE]);
}

void PlayerWorker::processingErrors(QString error)
{
    qDebug() << "Error: " << error;
}

void PlayerWorker::processingResponses(QString response, QString message)
{
    qDebug() << "Response: " << response << " " << message;

    if (response == "heartbeat") {
        emit serverIsAlive();
    }

    if (response == "play") {
        emit streamPlayed();
    }

    if (response == "stop") {
        emit streamStopped();
    }

    if (response == "pause") {
        emit streamPaused();
    }
}







