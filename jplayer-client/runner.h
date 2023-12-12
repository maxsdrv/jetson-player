#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QJsonObject>

class Runner : public QObject
{
    Q_OBJECT
public:
    explicit Runner(const QString& type, QObject *parent = nullptr);
    Runner(const QString& type, const QJsonObject& data);

    void setData(const QJsonObject& data);

    QString getType() const {
        return _type;
    }

    QJsonObject getData() const {
        return _data;
    }

    QByteArray toByteArray() const;
    static Runner fromByteArray(const QByteArray& bytes);

private:
    QString _type;
    QJsonObject _data;

};

#endif // RUNNER_H
