#ifndef PLAYERWORKER_H
#define PLAYERWORKER_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QThread>
#include <QJsonObject>

QT_BEGIN_NAMESPACE

class QNetworkAccessManager;
class QTimer;

QT_END_NAMESPACE

struct HttpRequestData {
    QString endpoint;
    enum class RequestType {
        GET,
        POST
    } requestType;
    QJsonObject data;
};


class PlayerWorker : public QObject
{
    Q_OBJECT
public:
    explicit PlayerWorker(QObject *parent = nullptr);
    ~PlayerWorker();

    void enqueueRequest(const HttpRequestData& request);
    void setupTimers();
    void setUrl(QString url);

private:
    QNetworkAccessManager *_networkManager;
    QThread _thread;
    QMutex _queueMutex;
    QMutex _processMutex;
    QQueue<HttpRequestData> _requestQueue;
    QString _serverUrl;
    QTimer* _connectionTimer;

    void sendRequest(const HttpRequestData& requestData);

public slots:
    void checkConnection();

private slots:
    void networkReply(QNetworkReply* reply);
    void processQueue();

signals:
    void responseReceived(const QString& response);
    void connectionEstablished();
    void connectionLost();
    void newRequestEnqueue();
};

#endif // PLAYERWORKER_H
