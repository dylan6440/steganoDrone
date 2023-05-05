#ifndef MQTTSEND_H
#define MQTTSEND_H

#include <QObject>
#include <QString>

class mqttSend: public QObject
{
    Q_OBJECT
public:
    explicit mqttSend(QObject *parent = nullptr);
    void sendDataToMqtt(const QString hostName, int16_t port, QString username, QString password, QString topic, QString data);
private:

};

#endif // MQTTSEND_H
