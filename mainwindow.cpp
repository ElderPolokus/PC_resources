#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpu.h"
#include "ram.h"
#include "disk.h"
#include "userinfo.h"
#include <QTimer>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkInterface>

MainWindow::MainWindow(const QString& strHost, int nPort, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_nNextBlockSize(0)
{
    ui->setupUi(this);
    // Timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer()));
    timer->start(1000);

    // Default image
    QPixmap pix(":/resources/img/pngwing.com.png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
    ui -> groupBox -> hide();

    //Подключение к серверу
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
//    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
//    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer()
{
    cpu cpu;
    ui -> pB_CPU -> setValue(cpu.cpu_value_int);

    ram ram;
    if(ram.err != "") {
        if((QMessageBox::critical(this, "Ошибка", ram.err, QMessageBox::Ok)) == QMessageBox::Ok) {
            qApp->exit();
        }
    }
    ui -> pB_RAM -> setValue(ram.ram_value_int);

    disk disk;
    ui -> label_DISK -> setText(disk.name_disk);
    ui -> pB_DISK -> setValue(disk.disk_value_int);

    //UserInfo
    UserInfo userinfo;
    ui ->  label_Name -> setText("Имя: " + userinfo.UserName);
    if(userinfo.IP_address != "") {
        ui -> label_IP_address -> setText("\nIP-адреса: " + userinfo.IP_address);
    } else {
        ui -> label_IP_address -> setText("\nНе возможно получить IP-адрес");
    }
    ui ->  label_PC_time -> setText("\nВремя работы ПК" + userinfo.PC_time);
}

void MainWindow::slotError(QAbstractSocket::SocketError err) {
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused." :
                     QString(m_pTcpSocket->errorString()));
    qDebug() << strError;
}

// Картинки ----------------------------------------------------------------
void MainWindow::on_action_Image_PC_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com.png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}


void MainWindow::on_action_Image_Printer_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com (1).png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}


void MainWindow::on_action_Image_Laptop_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com (2).png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}


void MainWindow::on_action_Image_Server_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com (3).png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}
// Картинки ----------------------------------------------------------------

//Вывод информации о пользователе (или скрыть)
void MainWindow::on_action_UserInfo_triggered()
{
    if(ui->groupBox -> isVisible()) {
        ui -> groupBox -> hide();
    } else {
        ui -> groupBox -> show();
    }
}

//Подключение к серверу
void MainWindow::on_action_ConnectToServer_triggered()
{
    QString strHost;
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
             strHost = address.toString();
        }
    }
    m_pTcpSocket->connectToHost(strHost, 2323);
}

