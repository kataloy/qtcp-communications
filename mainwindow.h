#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QKeyEvent>
#include <QByteArray>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct Init {
        int command = 1;
    };

    struct Start {
        int command = 2;
        int smNum;
        int smDir;
        int smSpeed;
        int smAcceleration;
    };

    struct Stop {
        int command = 3;
        int smStopMode;
    };

    struct Move {
        int command = 4;
        int smNum;
        int smSpeed;
        int smAcceleration;
        char smDistance;
    };

    struct Goto {
        int command = 5;
        int smNum;
        int smSpeed;
        int smAcceleration;
        char smPosition;
    };

    struct Led {
        int command = 256;
        int ledAction;
    };

private slots:
    void on_btn_init_clicked();
    void on_btn_start_clicked();
    void on_btn_stop_clicked();
    void on_btn_move_clicked();
    void on_btn_goto_clicked();
    void on_btn_led_clicked();
    void on_btn_connect_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket *tcpsocket;

};
#endif // MAINWINDOW_H
