#include <QCoreApplication>
#include "traitementimages.h"
#include "mqttsend.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QByteArray image_data;
    QMqttTopicName topicName;
    topicName.setName("/ynov/bordeaux/steganoDrone");

    traitementImages T;
    mqttSend MS;
    image_data = T.encodeImage(T.defaultPath, "37°42'41.9'S 144°59'33.0'E");
    MS.sendDataToMqtt("broker.emqx.io",1883,"","",topicName,image_data);
    return a.exec(); 
}
