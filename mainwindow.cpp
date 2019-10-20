#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->init_command->setText("1");
    ui->start_command->setText("2");
    ui->stop_command->setText("3");
    ui->move_command->setText("4");
    ui->goto_command->setText("5");
    ui->led_command->setText("256");
}

MainWindow::~MainWindow()
{
    tcpsocket->close();
    tcpsocket->disconnectFromHost();

    delete tcpsocket;
    delete ui;
}

void MainWindow::on_btn_init_clicked()
{
    Init init;
    QByteArray arrayInit;

    arrayInit.resize(20);
    arrayInit.insert(0, reinterpret_cast<char*> (&init), sizeof(init));

    tcpsocket->write(arrayInit.data(), 20);

    arrayInit.clear();
}

void MainWindow::on_btn_start_clicked()
{
    Start start;
    QByteArray arrayStart;

    start.smNum = ui->start_smNum->text().toInt();
    start.smDir = ui->start_smDir->text().toInt();
    start.smSpeed = ui->start_smSpeed->text().toInt();
    start.smAcceleration = ui->start_smAcceleration->text().toInt();

    if (start.smNum != 0 && start.smNum != 1 && start.smNum != 2 && start.smNum != 3) {
        QMessageBox::warning(this,"Warning", "Ошибка. Неправильные параметры.");
    }

    if (start.smDir != 0 && start.smDir != 1) {
        QMessageBox::warning(this,"Warning", "Ошибка. Неправильные параметры.");
    }

    arrayStart.resize(20);
    arrayStart.insert(0, reinterpret_cast<char*> (&start), sizeof(start));

    tcpsocket->write(arrayStart.data(), 20);

    arrayStart.clear();
}

void MainWindow::on_btn_stop_clicked()
{
    Stop stop;
    QByteArray arrayStop;

    stop.smStopMode = ui->stop_smStopMode->text().toInt();

    if (stop.smStopMode != 0 && stop.smStopMode != 1) {
        QMessageBox::warning(this,"Warning", "Ошибка. Неправильные параметры.");
    }

    arrayStop.resize(20);
    arrayStop.insert(0, reinterpret_cast<char*> (&stop), sizeof(stop));

    tcpsocket->write(arrayStop.data(), 20);

    arrayStop.clear();
}

void MainWindow::on_btn_move_clicked()
{
    Move move;
    QByteArray arrayMove;

    move.smNum = ui->move_smNum->text().toInt();
    move.smSpeed = ui->move_smSpeed->text().toInt();
    move.smAcceleration = ui->move_smAcceleration->text().toInt();
    move.smDistance = ui->move_smDistance->text().toInt();

    if (move.smNum != 0 && move.smNum != 1 && move.smNum != 2 && move.smNum != 3) {
        QMessageBox::warning(this,"Warning", "Ошибка. Неправильные параметры.");
    }

    arrayMove.resize(20);
    arrayMove.insert(0, reinterpret_cast<char*> (&move), sizeof(move));

    tcpsocket->write(arrayMove.data(), 20);

    arrayMove.clear();
}

void MainWindow::on_btn_goto_clicked()
{
    Goto go;
    QByteArray arrayGo;

    go.smNum = ui->goto_smNum->text().toInt();
    go.smSpeed = ui->goto_smSpeed->text().toInt();
    go.smAcceleration = ui->goto_smAcceleration->text().toInt();
    go.smPosition = ui->goto_smPosition->text().toInt();

    if (go.smNum != 0 && go.smNum != 1 && go.smNum != 2 && go.smNum != 3) {
        QMessageBox::warning(this,"Warning", "Ошибка. Неправильные параметры.");
    }

    arrayGo.resize(20);
    arrayGo.insert(0, reinterpret_cast<char*> (&go), sizeof(go));

    tcpsocket->write(arrayGo.data(), 20);

    arrayGo.clear();
}

void MainWindow::on_btn_led_clicked()
{
    Led led;
    QByteArray arrayLed;

    led.ledAction = ui->led_ledAction->text().toInt();

    if (led.ledAction != 1 && led.ledAction != 2 && led.ledAction != 3) {
        QMessageBox::warning(this,"Warning", "Ошибка. Неправильные параметры.");
    }

    arrayLed.resize(20);
    arrayLed.insert(0, reinterpret_cast<char*> (&led), sizeof(led));

    tcpsocket->write(arrayLed.data(), 20);

    arrayLed.clear();
}

void MainWindow::on_btn_connect_clicked()
{
    int port = ui->port->text().toInt();
    QString ip = ui->ip->text();

    tcpsocket = new QTcpSocket(this);

    tcpsocket->bind(QHostAddress("192.168.1.7"), 8001);
    tcpsocket->connectToHost(QHostAddress(ip), port);

    //connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
}
