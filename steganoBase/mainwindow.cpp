#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    if ((s_mqttHostName != NULL)&&(s_mqttPort != NULL)&&(s_mqttUserName != NULL)&&(s_mqttPassWord != NULL))
    {

    } else
    {
        ui->textBrowserMessage->setText("Connection Refuse \n \nAdding informations : \n\nHostname\nPort\nUsername\nPassword");
    }
}

void MainWindow::close()
{
    close();
}
