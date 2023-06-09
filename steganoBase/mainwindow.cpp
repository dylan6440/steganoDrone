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

    Client = new QMqttClient(this);
    Client->setHostname(s_mqttHostName);
    Client->setPort(s_mqttPort.toInt());
    Client->setUsername(s_mqttUserName);
    Client->setPassword(s_mqttPassWord);

    QObject::connect(Client, &QMqttClient::connected, [&]()
    {
        qDebug() << "Connected to MQTT broker.";

        qint32 qos_var = 2;

        if (!Client->subscribe(s_mqttTopic, qos_var))
        { 
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
        if (topic.name() == s_mqttTopic) {
              decodeImage(s_message);
            QImage image;
            QGraphicsScene *scene = new QGraphicsScene(this);
            image.loadFromData(s_message);
            QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            scene->addItem(pixmapItem);
            QRectF bounds = scene->itemsBoundingRect();
            ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
            ui->graphicsView->setScene(scene);

            qDebug() << "Image received and saved";
        }
    });

    Client->connectToHost();
}

void MainWindow::decodeImage(const QByteArray &s_message)
{
    QImage image;
    if (!image.loadFromData(s_message)) {
        qDebug() << "Failed to load image from message data.";
        return;
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

    ui->textBrowserMessage->setText(secretText);
}

void MainWindow::close()
{
    close();
}

void MainWindow::decodeMessage()
{

}
