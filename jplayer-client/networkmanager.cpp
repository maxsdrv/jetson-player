#include <QTimer>

#include "networkmanager.h"
#include "playerworker.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent},
      _playerWorker{new PlayerWorker()},
      _playerThread{new QThread()},
      _timer{new QTimer(this)}
{
    connect(_playerThread.get(), &QThread::started, this, &NetworkManager::setupTimers,Qt::QueuedConnection);
    connect(_playerWorker.get(), &PlayerWorker::streamPlayed, this, &NetworkManager::streamSuccessfullyPlayed, Qt::QueuedConnection);
    connect(_timer, &QTimer::timeout, _playerWorker.get(), &PlayerWorker::checkConnection, Qt::QueuedConnection);
    connect(_playerWorker.get(), &PlayerWorker::serverIsAlive, _timer, &QTimer::stop, Qt::QueuedConnection);

    connect(this, &NetworkManager::playRequested, _playerWorker.get(), &PlayerWorker::play, Qt::QueuedConnection);
    connect(this, &NetworkManager::stopRequested, _playerWorker.get(), &PlayerWorker::stop, Qt::QueuedConnection);
    connect(this, &NetworkManager::pauseRequested, _playerWorker.get(), &PlayerWorker::pause, Qt::QueuedConnection);

    _playerWorker->moveToThread(_playerThread.get());
    _playerThread->start();
}

NetworkManager::~NetworkManager()
{
    _playerThread->quit();
    _playerThread->wait();

    qDebug() << __func__;
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
    }
    qDebug() << __func__ << "url: " << url;
}

void NetworkManager::proceedResponse(const QString &response)
{
    qDebug() << "Response received: " << response;
}

void NetworkManager::proceedErrors(const QString &error)
{
    qDebug() << "Error occurred: " << error;
}

void NetworkManager::setupTimers()
{
    _timer->start(1000);
}






