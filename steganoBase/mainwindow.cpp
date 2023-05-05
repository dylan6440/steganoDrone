#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMqtt/QMqttClient>
#include <QDebug>
#include <QFile>

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
        QMqttClient Client;

        Client.setHostname(s_mqttHostName);
        Client.setPort(s_mqttPort);
        Client.setUsername(s_mqttUserName);
        Client.setPassword(s_mqttPassWord);

        QObject::connect(&Client, &QMqttClient::connected, [&]()
        {
            qDebug() << "Connected to MQTT broker.";

            qint32 qos_var = 2;

            if (!Client.subscribe(s_mqttTopic, qos_var))
            { // Souscription au topic contenant l'image
                qDebug() << "Error subscribing to topic:" << s_mqttTopic;
                return;
            } else {
                qDebug() << "Subscribed to topic:" << s_mqttTopic;
                 ui->textEdit_HNMQTT->setEnabled((False));
                 ui->textEdit_PMQTT->setEnabled((False));
                 ui->textEdit_UNMQTT->setEnabled((False));
                 ui->textEdit_PWMQTT->setEnabled((False));
                 ui->textEdit_topic->setEnabled((False));
                 ui->pushButtonConnection->setEnabled((False));
            }
                         });

QObject::connect(&Client, &QMqttClient::messageReceived, [&](const QByteArray &s_message, const QMqttTopicName &topic) {

    qDebug() << "Received message:" << s_message << "from topic:" << topic.name();

    if (topic.name() == s_mqttTopic) {
        decodeImage(s_message);
    }
});

        Client.connectToHost();

    } else
    {
        ui->textBrowserMessage->setText("Connection Refuse \n \nAdding informations : \n\nHostname\nPort\nUsername\nPassword\nTopic");
    }
}

void MainWindow::decodeImage(const QByteArray &s_message)
{
    // Charger l'image depuis le QByteArray
    QImage image;
    if (!image.load("/home/yanis/mqttYnov/DroneIMG37337.png")) {
        qDebug() << "Failed to load image from message data.";
        return;
    }

    // Extraire les bits du message caché
    QByteArray messageBytes;
    for (int32_t i = 0; i < image.width(); i++) {
        for (int32_t j = 0; j < image.height(); j++) {
            QRgb pixel = image.pixel(i, j);
            char_t byte = 0;
            byte |= (qRed(pixel) & 1);
            byte <<= 1;
            byte |= (qGreen(pixel) & 1);
            byte <<= 1;
            byte |= (qBlue(pixel) & 1);
            messageBytes.append(byte);
        }
    }

    // Décoder le message
    QString message = QString::fromUtf8(messageBytes);
    ui->textBrowserMessage->setText(message);
}

void MainWindow::close()
{
    close();
}

void MainWindow::decodeMessage()
{

}
