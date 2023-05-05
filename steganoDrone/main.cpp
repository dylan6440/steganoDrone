#include <QCoreApplication>
#include "traitementimages.h"
#include "mqttsend.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString image_data;

    traitementImages T;
    mqttSend MS;
    image_data = T.encodeImage(T.defaultPath, "lol");
    MS.sendDataToMqtt("broker.emqx.io",1883,"yanis","testynov","/ynov/bordeaux/steganoDrone",image_data);
    return a.exec();
}
