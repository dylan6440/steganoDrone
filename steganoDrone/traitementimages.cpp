#include "traitementimages.h"
#include "paql.h"
#include <QString>
#include <QImage>
#include <QtDebug>
#include <iostream>
#include <QFile>
#include <QColor>

traitementImages::traitementImages(QObject *parent)
    : QObject(parent)
{
    // initialisation des membres de la classe
}

QString traitementImages::encodeImage(QString imagePath, QString secretMessage)
{
    QFile file(imagePath);
    while (!file.exists()) {
        std::cout << "Entrez le chemin d'accès à l'image : ";
        std::string imagePath;
        std::cin >> imagePath;
    }
    // Charge l'image
    QImage image;
    if (!image.load(file.fileName())) {
        std::cerr << "Impossible de charger l'image." << std::endl;
        return "error 0";
    }
    std::cout << "Image chargée." << std::endl;
    QString message = secretMessage;
    QByteArray messageBytes = message.toUtf8();
    int32_t messageLength = messageBytes.size();
    int32_t byteIndex = 0;
    for (int32_t i = 0; i < image.width(); i++) {
        for (int32_t j = 0; j < image.height(); j++) {
            QRgb pixel = image.pixel(i, j);
            int32_t red = qRed(pixel);
            int32_t green = qGreen(pixel);
            int32_t blue = qBlue(pixel);
            if (byteIndex < messageLength) {
                char_t byte = messageBytes[byteIndex];
                red = (red & ~1) | (byte & 1);
                byte >>= 1;
                green = (green & ~1) | (byte & 1);
                byte >>= 1;
                blue = (blue & ~1) | (byte & 1);
                byteIndex++;
            }
            pixel = qRgb(red, green, blue);
            image.setPixel(i, j, pixel);
            if (byteIndex == messageLength - 1)break;
        }
        if (byteIndex == messageLength - 1)break;
    }
    std::cout << "Message caché dans l'image." << std::endl;
    QByteArray imageData;
    QDataStream stream(&imageData, QIODevice::WriteOnly);
    stream << image;
    QString encodedImage = QString::fromLatin1(imageData.toBase64().data());
    std::cout << "Image encodée en base64 : " << encodedImage.toStdString() << std::endl;
    file.close();
    return encodedImage;
}
