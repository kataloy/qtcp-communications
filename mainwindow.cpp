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
    ui->led_command->setText("6");



    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_init_clicked()
{

}

void MainWindow::on_btn_start_clicked()
{
    Start start;

    start.smNum = ui->start_smNum->text().toInt();
    start.smDir = ui->start_smDir->text().toInt();
    start.smSpeed = ui->start_smSpeed->text().toInt();
    start.smAcceleration = ui->start_smAcceleration->text().toInt();

    QByteArray arrayStart;

    arrayStart.resize(32);
    memmove(arrayStart.data(), &start, sizeof (start));

    tcpsocket->write(arrayStart.data(), 32);
}

void MainWindow::on_btn_stop_clicked()
{
    Stop stop;

    stop.smStopMode = ui->stop_smStopMode->text().toInt();
}

void MainWindow::on_btn_move_clicked()
{
    Move move;

    move.smNum = ui->move_smNum->text().toInt();
    move.smSpeed = ui->move_smSpeed->text().toInt();
    move.smAcceleration = ui->move_smAcceleration->text().toInt();
    move.smDistance = ui->move_smDistance->text().toInt();
}

void MainWindow::on_btn_goto_clicked()
{
    Goto go;
    go.smNum = ui->goto_smNum->text().toInt();
    go.smSpeed = ui->goto_smSpeed->text().toInt();
    go.smAcceleration = ui->goto_smAcceleration->text().toInt();
    go.smPosition = ui->goto_smPosition->text().toInt();
}

void MainWindow::on_btn_led_clicked()
{
    Led led;

    led.ledAction = ui->led_ledAction->text().toInt();

    QByteArray arrayLed;

    arrayLed.resize(20);
    memmove(arrayLed.data(), &led, sizeof (led));

    qDebug() << arrayLed;

    tcpsocket->write(arrayLed.data(), 20);
}

void MainWindow::on_btn_connect_clicked()
{
    int port = ui->port->text().toInt();
    QString ip = ui->ip->text();

    tcpsocket = new QTcpSocket(this);

    tcpsocket->bind(QHostAddress("192.168.1.2"), 8001);
    tcpsocket->connectToHost(QHostAddress(ip), port);


    qDebug() << ip << port;
}
