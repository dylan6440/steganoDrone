#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButtonConnection,&QPushButton::clicked,this,&MainWindow::mqttConnection);
    connect(ui->pushButtonClose,&QPushButton::clicked,this,&MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mqttConnection()
{
    s_mqttHostName = ui->textEdit_HNMQTT->toPlainText();
    s_mqttPort = ui->textEdit_PMQTT->toPlainText();
    s_mqttUserName = ui->textEdit_UNMQTT->toPlainText();
    s_mqttPassWord = ui->textEdit_PWMQTT->toPlainText();
    s_mqttTopic = ui->textEdit_topic->toPlainText();



    if ((s_mqttHostName != NULL)&&(s_mqttPort != NULL)&&(s_mqttUserName != NULL)&&(s_mqttPassWord != NULL))
    {
        Client = new QMqttClient(this);
        //        QMqttClient Client;

        Client->setHostname(s_mqttHostName);
        Client->setPort(s_mqttPort.toInt());
        Client->setUsername(s_mqttUserName);
        Client->setPassword(s_mqttPassWord);

        QObject::connect(Client, &QMqttClient::connected, [&]()
        {
            qDebug() << "Connected to MQTT broker.";

            qint32 qos_var = 2;

            if (!Client->subscribe(s_mqttTopic, qos_var))
            { // Souscription au topic contenant l'image
                qDebug() << "Error subscribing to topic:" << s_mqttTopic;
                return;
            } else {
                qDebug() << "Subscribed to topic:" << s_mqttTopic;
                ui->textEdit_HNMQTT->setEnabled((false));
                ui->textEdit_PMQTT->setEnabled((false));
                ui->textEdit_UNMQTT->setEnabled((false));
                ui->textEdit_PWMQTT->setEnabled((false));
                ui->textEdit_topic->setEnabled((false));
                ui->pushButtonConnection->setEnabled((false));
            }
        });

        QObject::connect(Client, &QMqttClient::messageReceived, [&](const QByteArray &s_message, const QMqttTopicName &topic) {


            qDebug() << "Received message:" << s_message << "from topic:" << topic.name();

            // Vérifier que le message est une image
            if (topic.name() == s_mqttTopic) {
                decodeImage(s_message);
                // Enregistrer l'image dans un fichier
                //                QFile file("/home/yanis/received_image.png");
                //                if (!file.open(QIODevice::WriteOnly)) {
                //                    qDebug() << "Error opening file for writing";
                //                    return;
                //                }
                //                file.write(message);
                //                file.close();
                ui->textBrowserMessage->setText(s_message);


                decodeImage(s_message);


                QImage image;
                QGraphicsScene *scene = new QGraphicsScene(this);

                image.loadFromData(s_message);

                // Créer un QGraphicsPixmapItem avec l'image convertie
                QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));

                // Ajouter le QGraphicsPixmapItem à la scène
                scene->addItem(pixmapItem);






                //                QPixmap image(s_message);
                //                scene->addPixmap(image);
                QRectF bounds = scene->itemsBoundingRect();
                ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
                ui->graphicsView->setScene(scene);


                qDebug() << "Image received and saved";
            }
        });


        Client->connectToHost();

    } else
    {

        ui->textBrowserMessage->setText("Connection Refuse \n \nAdding informations : \n\nHostname\nPort\nUsername\nPassword\nTopic");
    }
}

void MainWindow::decodeImage(QByteArray codedImage)
{
    // Load the image
    QImage image;
    if (!image.loadFromData(codedImage)) {
        std::cerr << "Impossible de charger l'image." << std::endl;
//        return "error 0";
    }
    std::cout << "Image chargée." << std::endl;

    // Décoder les bits LSB de chaque pixel de l'image pour récupérer les données cachées
    QByteArray binaryData;
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            binaryData.append(pixelColor.red() & 0x01);
            binaryData.append(pixelColor.green() & 0x01);
            binaryData.append(pixelColor.blue() & 0x01);
        }
    }
    int32_t binarySize = binaryData.size();
    // Convertir la séquence de bits en une chaîne de caractères
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
//    return secretText;
}



void MainWindow::close()
{
    close();
}

void MainWindow::decodeMessage()
{

}
