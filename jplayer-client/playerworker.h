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

    void setupTimers();
    void connectionTimerStop();
    void setUrl(QString url);
    void play();
    void stop();

private:
    QNetworkAccessManager *_networkManager;
    PlayerReceiver* _playerReceiver;
    PlayerSender* _playerSender;
    QThread _thread;
    QMutex _queueMutex;
    QQueue<PlayerSender*> _requestQueue;
    QString _serverUrl;
    QTimer* _connectionTimer;

    void sendRequest(PlayerSender* requestData);

    void senderConnections();
    void receiverConnecions();

public slots:
    void checkConnection();

private slots:
    void processingErrors(QString error);
    void processingResponses(QString response, QString message);

signals:
    void enqueueRequest(QString endpoint, const QByteArray &data);
    void enqueueRequest(QString endpoint);
    void urlUpdated(QString url);
};

#endif // PLAYERWORKER_H
