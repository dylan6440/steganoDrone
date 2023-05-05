#ifndef TRAITEMENTIMAGES_H
#define TRAITEMENTIMAGES_H

#include <QObject>
#include <QString>

class traitementImages : public QObject
{
    Q_OBJECT
public:
    explicit traitementImages(QObject *parent = nullptr);
    QString encodeImage (QString imagePath, QString secretMessage);
    QString defaultPath = "./Images/DroneIMG37337.png";
};

#endif // TRAITEMENTIMAGES_H
