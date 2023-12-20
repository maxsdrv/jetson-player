#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkReply>
#include <QQmlApplicationEngine>

QT_BEGIN_NAMESPACE

class PlayerWorker;
class QTimer;

QT_END_NAMESPACE

class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString response READ response NOTIFY responseChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    QString response() const;

    QString url() const {
        return _url;
    }

    void setUrl(QString url);

signals:
    void responseChanged();
    void urlChanged();
    void streamSuccessfullyPlayed();
    void playRequested();
    void stopRequested();
    void pauseRequested();

private slots:
    void proceedResponse(const QString& response);
    void proceedErrors(const QString& error);
    void setupTimers();

private:
    QString m_response;
    QString _url;
    QSharedPointer<PlayerWorker> _playerWorker;
    QSharedPointer<QThread> _playerThread;
    QTimer *_timer;
};

#endif // NETWORKMANAGER_H
