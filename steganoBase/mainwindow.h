#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void getBroker(void);
    void getTopic(void);
    void mqttConnection(void);
    void close(void);


private:
    Ui::MainWindow *ui;
    QString s_mqttTopic;
    QString s_mqttBroker;
    QString s_message;
    QString s_image;
};

#endif // MAINWINDOW_H
