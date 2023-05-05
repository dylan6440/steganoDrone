#include "mqttsend.h"
#include <QCoreApplication>
#include <QtMqtt/QMqttClient>
#include <QDebug>
#include <QFile>
#include <QTimer>


mqttSend::mqttSend(QObject *parent)
    :QObject(parent)
{
    // initialisation des membres de la classe
}

void mqttSend::sendDataToMqtt(const QString hostName, int16_t port, QString username, QString password, const QMqttTopicName &topic, QString data)
{
    client = new QMqttClient(this);

    client->setHostname(hostName);
    client->setPort(port);
    client->setUsername(username);
    client->setPassword(password);

    int16_t reconnectInterval = 5000; // 5 seconds

     QObject::connect(client, &QMqttClient::stateChanged, [&](QMqttClient::ClientState state) {
         qDebug() << "Client state:" << state;

        qint32 qos_var = 2;
        QByteArray image_data = data.toUtf8();

        // Publier l'image sur MQTT
         if (state == QMqttClient::Connected) {
            if (!client->publish(topic.name(), image_data, qos_var)) {
                qDebug() << "Error publishing message to topic:" << topic.name();
            } else {
                qDebug() << "Published image to topic:" << topic.name();
            }
         } else if (state == QMqttClient::Disconnected) {
            // Start a timer to try to reconnect
            QTimer::singleShot(reconnectInterval, [&]() {
                qDebug() << "Attempting to reconnect...";
                client->connectToHost();
            });
         }
    });

     client->connectToHost();

}