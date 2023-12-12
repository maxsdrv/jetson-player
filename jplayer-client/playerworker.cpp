#include <QThread>
#include <QMutex>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>

#include "playerworker.h"
#include "runner.h"
#include "playerreceiver.h"
#include "playersender.h"

namespace {
enum class MessageType {
    HEARTBEAT,
    PLAY,
    STOP
};
QMap<MessageType, QString> messageTypes {
    {MessageType::HEARTBEAT, "/heartbeat"},
    {MessageType::PLAY, "/play"},
    {MessageType::STOP, "/stop"}
};
}

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
    connect(this, QOverload<QString, const QByteArray&>::of(&PlayerWorker::enqueueRequest),
            _playerSender, QOverload<QString, const QByteArray&>::of(&PlayerSender::sendData));

    connect(this, QOverload<QString>::of(&PlayerWorker::enqueueRequest),
            _playerSender, QOverload<QString>::of(&PlayerSender::sendData));

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

    //PlayerSender *request = new PlayerSender{ RequestType::GET, "/heartbeat", messageData, this};

    //enqueueRequest(request);
    emit enqueueRequest(messageTypes[MessageType::HEARTBEAT]);
}

void PlayerWorker::play()
{

}

void PlayerWorker::stop()
{

}

//void PlayerWorker::networkReply(QNetworkReply* reply)
//{
    /*if (reply->error()) {

        emit badRequest(reply->errorString());

    } else {
        QByteArray responseByte = reply->readAll();
        auto message = Runner::fromByteArray(responseByte);

        auto data = message.getData();
        auto type = message.getType();

        emit responseReceived(type);

        //_connectionTimer->stop();
    }

    reply->deleteLater();*/
//}

void PlayerWorker::processingErrors(QString error)
{
    qDebug() << "Error: " << error << "\n";
}

void PlayerWorker::processingResponses(QString response)
{
    qDebug() << "Response: " << response << "\n";
}







