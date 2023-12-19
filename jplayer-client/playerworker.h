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
    explicit PlayerWorker(QObject *parent = nullptr);
    ~PlayerWorker();

    /**
     * @brief setupTimers - setup timers
     */
    void setupTimers();
    /**
     * @brief connectionTimerStop - stop connection timer
     */
    void connectionTimerStop();
    /**
     * @brief setUrl - set url
     * @param url - url
     */
    void setUrl(QString url);
    /**
     * @brief play - play video from server
     */
    void play();
    /**
     * @brief stop - stop video from server
     */
    void stop();

private:
    /**
     * @brief The MessageType enum - types of messages
     */
    enum class MessageType {
        HEARTBEAT,
        PLAY,
        STOP
    };
    /**
     * @brief messageTypes - map of message types and endpoints
      */
    QMap<MessageType, QString> messageTypes {
        {MessageType::HEARTBEAT, "/heartbeat"},
        {MessageType::PLAY, "/play"},
        {MessageType::STOP, "/stop"}
    };

private:
    QNetworkAccessManager *_networkManager;
    PlayerReceiver* _playerReceiver;
    PlayerSender* _playerSender;
    QThread _thread;
    QMutex _queueMutex;
    QQueue<PlayerSender*> _requestQueue;
    QString _serverUrl;
    QTimer* _connectionTimer;

    void senderConnections();
    void receiverConnecions();

public slots:
    /**
     * @brief checkConnection - check connection with server
     */
    void checkConnection();

private slots:
    /**
     * @brief processingErrors - processing errors from server
     * @param error - error message
     */
    void processingErrors(QString error);
    /**
     * @brief processingResponses - processing response from server
     * @param response - type of response message
     * @param message - message from server
     */
    void processingResponses(QString response, QString message);

signals:
    /**
     * @brief enqueuePostRequest - enqueue post request
     * @param endpoint - endpoint
     * @param data - data to send to server
     */
    void enqueuePostRequest(QString endpoint, const QByteArray &data);
    /**
     * @brief enqueueGetRequest - enqueue get request
     * @param endpoint - endpoint
     */
    void enqueueGetRequest(QString endpoint);
    /**
     * @brief urlUpdated - url updated
     * @param url - url
     */
    void urlUpdated(QString url);
    /**
     * @brief streamPlayed - stream played
     */
    void streamPlayed();
};

#endif // PLAYERWORKER_H
