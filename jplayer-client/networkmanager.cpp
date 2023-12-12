#include "networkmanager.h"
#include "playerworker.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, networkManager{new QNetworkAccessManager(this)},
      _playerWorker{new PlayerWorker(this)}
{

    qDebug() << __func__;
    connect(this, &NetworkManager::urlChanged, _playerWorker, &PlayerWorker::checkConnection, Qt::QueuedConnection);
    //connect(_playerWorker, &PlayerWorker::responseReceived, this, &NetworkManager::proceedResponse, Qt::QueuedConnection);
    //connect(_playerWorker, &PlayerWorker::badRequest, this, &NetworkManager::proceedErrors, Qt::QueuedConnection);
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

void NetworkManager::proceedResponse(const QString &response)
{
    qDebug() << "Response received: " << response;
}

void NetworkManager::proceedErrors(const QString &error)
{
    qDebug() << "Error occurred: " << error;
}






