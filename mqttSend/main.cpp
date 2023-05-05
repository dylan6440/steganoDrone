#include <QCoreApplication>
#include <QtMqtt/QMqttClient>
#include <QDebug>
#include <QFile>

int main(int argc_var, char *argv_t[])
{
    QCoreApplication A(argc_var, argv_t);

    QMqttClient Client;

    Client.setHostname("broker.emqx.io");
    Client.setPort(1883);
    Client.setUsername("yanis");
    Client.setPassword("testynov");

    QObject::connect(&Client, &QMqttClient::connected, [&]() {
        qDebug() << "Connected to MQTT broker.";

        QString s_topic = "/ynov/bordeaux/steganoDrone";
        qint32 qos_var = 2;

        // Charger l'image (à modifier)
        QFile file("/home/yanis/mqttYnov/DroneIMG37337.png");
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Error opening file";
            return;
        }
        QByteArray image_data = file.readAll();

        // Publier l'image sur MQTT
        if (!Client.publish(s_topic, image_data, qos_var)) {
            qDebug() << "Error publishing message to topic:" << s_topic;
        } else {
            qDebug() << "Published image to topic:" << s_topic;
        }
    });

    Client.connectToHost();

    return A.exec();
}
