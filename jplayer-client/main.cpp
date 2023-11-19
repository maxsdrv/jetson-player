#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "networkmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<NetworkManager>("network_manager", 1, 0, "Network");

    const QUrl url(u"qrc:/media-player/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
