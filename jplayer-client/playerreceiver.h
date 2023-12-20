#ifndef PLAYERRECEIVER_H
#define PLAYERRECEIVER_H

#include <QObject>
#include <QNetworkReply>

class PlayerReceiver : public QObject
{
    Q_OBJECT
public:
    PlayerReceiver();
    ~PlayerReceiver();

public slots:
    void networkReply(QNetworkReply* reply);

signals:
    void badRequest(QString error);
    void responseReceived(QString response, QString message);
};

#endif // PLAYERRECEIVER_H
