#include "traitementimages.h"
#include "paql.h"
#include <QString>
#include <QImage>
#include <QtDebug>
#include <iostream>
#include <QFile>
#include <QColor>
#include <QImageWriter>
#include <QBuffer>
#include <QPixmap>

traitementImages::traitementImages(QObject *parent)
    : QObject(parent)
{
}

QByteArray traitementImages::encodeImage(QString imagePath, QString secretMessage)
{

    QFile file(imagePath);

    while (!file.exists()) {
        std::cout << "Entrez le chemin d'accès à l'image : ";
        std::string imagePath;
        std::cin >> imagePath;
    }
    QImage image;

    if (!image.load(imagePath)) {
        std::cerr << "Impossible de charger l'image." << std::endl;
        return QByteArray();
    }

    image = image.convertToFormat(QImage::Format_RGB32);

    QByteArray secretData = secretMessage.toUtf8() + "!";
    QByteArray binaryData;
    for (int i = 0; i < secretData.size(); ++i) {
        char byte = secretData.at(i);
        for (int j = 0; j < 8; ++j) {
            binaryData.append((byte & 0x80) >> 7);
            byte <<= 1;
        }
    }

    for (int i = 0; i < 8; ++i) {
        binaryData.append('\0');
        if(binaryData.size() % 3 == 0)break;
    }

    int dataIdx = 0;
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            if (dataIdx >= binaryData.size()) {
                break;
            }
            pixelColor.setRed((pixelColor.red() & 0xFE) | binaryData.at(dataIdx++));
            pixelColor.setGreen((pixelColor.green() & 0xFE) | binaryData.at(dataIdx++));
            pixelColor.setBlue((pixelColor.blue() & 0xFE) | binaryData.at(dataIdx++));
            image.setPixelColor(x, y, pixelColor);
            if (dataIdx >= binaryData.size()) {
                break;
            }
        }
        if (dataIdx >= binaryData.size()) {
            break;
        }
    }

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    std::cout << "Message caché dans l'image." << std::endl;
    file.close();
    return imageData;
}

QString traitementImages::decodeImage(QByteArray codedImage)
{
    QImage image;
    if (!image.loadFromData(codedImage)) {
        std::cerr << "Impossible de charger l'image." << std::endl;
        return "error 0";
    }
    std::cout << "Image chargée." << std::endl;

    QByteArray binaryData;
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            binaryData.append(pixelColor.red() & 0x01);
            binaryData.append(pixelColor.green() & 0x01);
            binaryData.append(pixelColor.blue() & 0x01);
        }
    }
    QByteArray secretData;
    for (int32_t i = 0; i < binaryData.size(); i += 8) {
        int32_t byte = 0;
        for (int32_t j = 0; j < 8; ++j) {
            byte <<= 1;
            byte |= binaryData.at(i+j);
        }
        if (byte == '!')break;
        secretData.append(byte);
    }

    std::cout << "Message extrait de l'image." << std::endl;
    QString secretText = QString::fromUtf8(secretData);
    std::cout << "Message : " << secretText.toStdString() << std::endl;
    return secretText;
}
