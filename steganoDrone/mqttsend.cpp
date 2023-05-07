#include "mqttsend.h"
#include <QCoreApplication>
#include <QtMqtt/QMqttClient>
#include <QDebug>
#include <QFile>
#include <QTimer>

mqttSend::mqttSend(QObject *parent)
    :QObject(parent)
{
}

void mqttSend::sendDataToMqtt(const QString hostName, int16_t port, QString username, QString password, const QMqttTopicName &topic, QByteArray data)
{
    client = new QMqttClient(this);

    client->setHostname(hostName);
    client->setPort(port);
    client->setUsername(username);
    client->setPassword(password);
    client->setWillQoS(2);

    int16_t reconnectInterval = 5000; 

    client->connectToHost();

     QObject::connect(client, &QMqttClient::stateChanged, [&](QMqttClient::ClientState state) {

        qint8 qos_var = 2;
        QByteArray image_data = data;

        qDebug() << "Client state:" << state;

         if (state == QMqttClient::Connected) {
            if (!client->publish(topic.name(), image_data, qos_var)) {
                qDebug() << "Error publishing message to topic:" << topic.name();
            } else {
                qDebug() << "Published image to topic:" << topic.name();
                QTimer::singleShot(5000, [=]() {
                    client->disconnectFromHost();
                    qDebug() << "Client state:" << state;
                    exit(0);
                });
            }
         } else if (state == QMqttClient::Disconnected) {
            QTimer::singleShot(reconnectInterval, [&]() {
                qDebug() << "Attempting to reconnect...";
                client->connectToHost();
            });
         }
    });
}
