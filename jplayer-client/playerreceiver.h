#ifndef PLAYERRECEIVER_H
#define PLAYERRECEIVER_H

#include <QObject>
#include <QNetworkReply>

class PlayerReceiver : public QObject
{
    Q_OBJECT
public:
    explicit PlayerReceiver(QObject* parent = nullptr);
    ~PlayerReceiver();

public slots:
    void networkReply(QNetworkReply* reply);

signals:
    void badRequest(QString error);
    void responseReceived(QString response);
};

#endif // PLAYERRECEIVER_H
