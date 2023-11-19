#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQmlApplicationEngine>

class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString response READ response NOTIFY responseChanged)
public:
    explicit NetworkManager(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest(const QString& url);
    QString response() const;

signals:
    void responseChanged();

private slots:
    void networkReply(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
    QString m_response;
};

#endif // NETWORKMANAGER_H
