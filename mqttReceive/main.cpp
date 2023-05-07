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

        if (!Client.subscribe(s_topic, qos_var)) { 
            qDebug() << "Error subscribing to topic:" << s_topic;
            return;
        } else {
            qDebug() << "Subscribed to topic:" << s_topic;
        }
    });


    QObject::connect(&Client, &QMqttClient::messageReceived, [&](const QByteArray &message, const QMqttTopicName &topic) {
        qDebug() << "Received message:" << message << "from topic:" << topic.name();

        if (topic.name() == "/ynov/bordeaux/steganoDrone") {
            QFile file("/home/yanis/received_image.png");
            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << "Error opening file for writing";
                return;
            }
            file.write(message);
            file.close();
            qDebug() << "Image received and saved";
        }
    });

    Client.connectToHost();

    return A.exec();
}






