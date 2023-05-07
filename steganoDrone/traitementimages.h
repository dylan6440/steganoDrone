#ifndef TRAITEMENTIMAGES_H
#define TRAITEMENTIMAGES_H

#include <QObject>
#include <QString>

class traitementImages : public QObject
{
    Q_OBJECT
public:
    explicit traitementImages(QObject *parent = nullptr);
    QByteArray encodeImage (QString imagePath, QString secretMessage);
    QString decodeImage (QByteArray codedImage);
    QString defaultPath = "../steganoDrone/Images/DroneIMG37337.png";
};

#endif // TRAITEMENTIMAGES_H
