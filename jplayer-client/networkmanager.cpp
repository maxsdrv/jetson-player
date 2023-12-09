#include "networkmanager.h"
#include "playerworker.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, networkManager{new QNetworkAccessManager(this)},
      _playerWorker{new PlayerWorker(this)}
{

    qDebug() << __func__;
    connect(this, &NetworkManager::urlChanged, _playerWorker, &PlayerWorker::checkConnection);
    connect(_playerWorker, &PlayerWorker::connectionEstablished, this, &NetworkManager::serverIsAlive);
    connect(_playerWorker, &PlayerWorker::connectionLost, this, &NetworkManager::serverIsDead);
}

NetworkManager::~NetworkManager()
{
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

void NetworkManager::setUrl(QString url)
{
    if (_url != url && !url.isEmpty()) {
        _url = url;
        _playerWorker->setUrl(_url);
        _playerWorker->setupTimers();
    }
    qDebug() << __func__ << "url: " << url;

    emit urlChanged();
}

void NetworkManager::serverIsAlive() {
    qDebug() << __func__;
}

void NetworkManager::serverIsDead()
{
    qDebug() << __func__;
}




