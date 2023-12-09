#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQmlApplicationEngine>

QT_BEGIN_NAMESPACE

class PlayerWorker;

QT_END_NAMESPACE

class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString response READ response NOTIFY responseChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    Q_INVOKABLE void sendRequest(const QString& url);

    QString response() const;

    QString url() const {
        return _url;
    }

    void setUrl(QString url);

signals:
    void responseChanged();
    void urlChanged();

private slots:
    void serverIsAlive();
    void serverIsDead();

private:
    QNetworkAccessManager* networkManager;
    QString m_response;
    QString _url;
    PlayerWorker* _playerWorker;
};

#endif // NETWORKMANAGER_H
