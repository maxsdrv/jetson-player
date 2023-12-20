#ifndef PLAYERWORKER_H
#define PLAYERWORKER_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QThread>
#include <QJsonObject>

QT_BEGIN_NAMESPACE

class QNetworkAccessManager;
class PlayerSender;
class PlayerReceiver;
class QTimer;

QT_END_NAMESPACE

class PlayerWorker : public QObject
{
    Q_OBJECT
public:
    PlayerWorker();
    ~PlayerWorker();

    void setUrl(QString url);

private:
    enum class MessageType {
        HEARTBEAT,
        PLAY,
        PAUSE,
        STOP
    };

    QMap<MessageType, QString> messageTypes {
        {MessageType::HEARTBEAT, "/heartbeat"},
        {MessageType::PLAY, "/play"},
        {MessageType::PAUSE, "/pause"},
        {MessageType::STOP, "/stop"}
    };

private:
    QScopedPointer<QNetworkAccessManager> _networkManager;
    QScopedPointer<PlayerReceiver> _playerReceiver;
    QScopedPointer<PlayerSender> _playerSender;
    QMutex _queueMutex;
    QQueue<PlayerSender*> _requestQueue;
    QString _serverUrl;

    void senderConnections();
    void receiverConnecions();

public slots:
    void checkConnection();
    void play();
    void stop();
    void pause();

private slots:
    void processingErrors(QString error);
    void processingResponses(QString response, QString message);

signals:
    void enqueuePostRequest(QString endpoint, const QByteArray &data);
    void enqueueGetRequest(QString endpoint);
    void urlUpdated(QString url);
    void serverIsAlive();
    void streamPlayed();
    void streamPaused();
    void streamStopped();
};

#endif // PLAYERWORKER_H
