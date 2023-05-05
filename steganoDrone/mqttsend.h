#ifndef MQTTSEND_H
#define MQTTSEND_H

#include <QObject>
#include <QString>
#include <QtMqtt/QMqttClient>

class mqttSend: public QObject
{
    Q_OBJECT
public:
    explicit mqttSend(QObject *parent = nullptr);
    void sendDataToMqtt(const QString hostName, int16_t port, QString username, QString password, const QMqttTopicName &topic, QString data);
private:
    QMqttClient *client;
};

#endif // MQTTSEND_H
