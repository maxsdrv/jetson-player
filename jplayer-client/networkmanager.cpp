#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, networkManager{new QNetworkAccessManager(this)}
{
    //connect(networkManager, &QNetworkAccessManager::finished, this, &NetworkManager::networkReply);
    qDebug() << __func__;
}

void NetworkManager::sendRequest(const QString &url)
{
    QNetworkRequest request((QUrl(url)));
    networkManager->get(request);
}

QString NetworkManager::response() const
{
    return m_response;
}

void NetworkManager::networkReply(QNetworkReply *reply)
{
    if (reply->error()) {
        m_response = "Error: " + reply->errorString();
    } else {
        QByteArray response = reply->readAll();
        m_response = "Server Response: " + QString(response);
    }

    emit responseChanged();

    reply->deleteLater();
}


