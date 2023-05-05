#include <QCoreApplication>
#include "traitementimages.h"
#include "mqttsend.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString image_data;
    QMqttTopicName topicName;
    topicName.setName("testynov_stegano");

    traitementImages T;
    mqttSend MS;
    image_data = T.encodeImage(T.defaultPath, "lol");
    MS.sendDataToMqtt("broker.emqx.io",1883,"","",topicName,image_data);
    return a.exec();
}
