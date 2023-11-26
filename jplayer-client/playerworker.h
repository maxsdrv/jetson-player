#ifndef PLAYERWORKER_H
#define PLAYERWORKER_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QThread>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
QT_END_NAMESPACE

class PlayerWorker : public QObject
{
    Q_OBJECT
public:
    explicit PlayerWorker(QObject *parent = nullptr);
    ~PlayerWorker();

    void enqueueRequest(const QString& request);

private:
    QNetworkAccessManager *_networkManager;
    QThread _thread;
    QMutex _queueMutex;
    QQueue<QString> _requestQueue;
    QString _serverUrl;

    void sendRequest(const QString& request);
    void checkConnection();

signals:
    void responseReceived(const QString& response);
    void connectionEstablished();
    void connectionLost();
};

#endif // PLAYERWORKER_H
