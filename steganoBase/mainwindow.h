#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paql.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public  slots:
    void mqttConnection(void);
    void close(void);


private:
    Ui::MainWindow *ui;
    QString s_mqttHostName;
    QString s_mqttPort;
    QString s_mqttUserName;
    QString s_mqttPassWord;
    QString s_message;
    QString s_image;
};

#endif // MAINWINDOW_H
