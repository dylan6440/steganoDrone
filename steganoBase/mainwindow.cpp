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
            }
        };

        QObject::connect(&Client, &QMqttClient::messageReceived, [&](const QByteArray &s_message, const QMqttTopicName &topic) {

            qDebug() << "Received message:" << s_message << "from topic:" << topic.name();

            // Vérifier que le message est une image
            if (topic.name() == s_mqttTopic) {
                // Enregistrer l'image dans un fichier
//                QFile file("/home/yanis/received_image.png");
//                if (!file.open(QIODevice::WriteOnly)) {
//                    qDebug() << "Error opening file for writing";
//                    return;
//                }
//                file.write(message);
//                file.close();
                ui->textBrowserMessage->setText(s_message);


                QPixmap image(s_message);
                QGraphicsScene *scene = new QGraphicsScene(this);
                scene->addPixmap(image);
                QRectF bounds = scene->itemsBoundingRect();
                ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
                ui->graphicsView->setScene(scene);

                qDebug() << "Image received and saved";
            }
        });

        Client.connectToHost();

    } else
    {
        ui->textBrowserMessage->setText("Connection Refuse \n \nAdding informations : \n\nHostname\nPort\nUsername\nPassword\nTopic");
    }
}

void MainWindow::close()
{
    close();
}

void MainWindow::decodeMessage()
{

}
