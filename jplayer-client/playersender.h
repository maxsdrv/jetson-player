#ifndef PLAYERSENDER_H
#define PLAYERSENDER_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QNetworkAccessManager>

struct HttpRequestData {
    QString endpoint;
    enum class RequestType {
        GET,
        POST
    } requestType;
    QByteArray data;
};



class PlayerSender : public QObject
{
    Q_OBJECT
public:
    explicit PlayerSender(QNetworkAccessManager* netManager, QObject* parent = nullptr);
    ~PlayerSender();

    HttpRequestData dequeueRequest();

private:
    QNetworkAccessManager *_networkManager;
    QQueue<HttpRequestData> _requestQueue;
    QMutex _queueMutex;
    QString _serverUrl;

    void enqueueRequest(const HttpRequestData& requestData);
    void processQueue();
    void sendRequest(const HttpRequestData& requestData);

public slots:
    void prepareGetRequest(QString endpoint);
    void preparePostRequest(QString endpoint, const QByteArray& data);
    void setUrl(QString url);

signals:
    void newRequestEnqueue();
    // void enqueueRequest(QString endpoint, const QByteArray &data);
    // void enqueueRequest(QString endpoint);
};

#endif // PLAYERSENDER_H
