#include <QJsonDocument>

#include "runner.h"

Runner::Runner(const QString &type, QObject* object) : QObject{object}, _type{type}
{

}

Runner::Runner(const QString &type, const QJsonObject &data) : _type{type}, _data{data}
{

}

QByteArray Runner::toByteArray() const
{
    QJsonObject runnerObject;
    runnerObject["type"] = _type;
    runnerObject["data"] = _data;
    return QJsonDocument(runnerObject).toJson();
}

Runner Runner::fromByteArray(const QByteArray &bytes)
{
    QJsonDocument runnerDocument = QJsonDocument::fromJson(bytes);
    QJsonObject runnerObject = runnerDocument.object();
    QString type = runnerObject["type"].toString();
    QJsonObject data = runnerObject["data"].toObject();
    return Runner{type, data};
}

