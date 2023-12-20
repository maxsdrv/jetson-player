#include <QDebug>

#include "playerreceiver.h"
#include "runner.h"

PlayerReceiver::PlayerReceiver()
{
}

PlayerReceiver::~PlayerReceiver()
{
    qDebug() << __func__;
}

void PlayerReceiver::networkReply(QNetworkReply *reply)
{
    if (reply->error()) {

        emit badRequest(reply->errorString());

    } else {
        QByteArray responseByte = reply->readAll();
        auto message = Runner::fromByteArray(responseByte);

        auto data = message.getData();
        auto type = message.getType();

        emit responseReceived(type, data.value("message").toString());
    }

    reply->deleteLater();

}
