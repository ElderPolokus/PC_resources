#include "pc_resources.h"
#include "ui_pc_resources.h"
#include "cpu.h"
#include "ram.h"
#include "disk.h"
#include "userinfo.h"
#include <QTimer>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkInterface>

pc_resources::pc_resources(const QString& strHost, int nPort, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pc_resources)
    , m_nNextBlockSize(0)
{
    ui->setupUi(this);
    // Timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer()));
    timer->start(1000);

    // Default image
    getImage(1);
    ui -> groupBox -> hide();

    //Подключение к серверу
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(disconnected()), SLOT(slotDisconnected()));
//    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

pc_resources::~pc_resources()
{
    delete ui;
}

void pc_resources::timer()
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

void pc_resources::slotError(QAbstractSocket::SocketError err) {
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused." :
                     QString(m_pTcpSocket->errorString()));
    qDebug() << strError;
}

void pc_resources::slotConnected() {
    QMessageBox::information(this, "Подключение к серверу", "Соединение установлено!");
    ui -> action_ConnectToServer -> setText("Отключиться от сервера");
}

void pc_resources::slotDisconnected() {
    QMessageBox::information(this, "Отсоединение от сервера", "Вы успешно отсоединились!");
    ui -> action_ConnectToServer -> setText("Подключиться к серверу");
}

//Подключение к серверу
void pc_resources::on_action_ConnectToServer_triggered()
{
    QString strHost;
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
             strHost = address.toString();
        }
    }

    if(m_pTcpSocket->state() == QTcpSocket::ConnectedState) {
        m_pTcpSocket->disconnectFromHost();
    } else {
        m_pTcpSocket->connectToHost(strHost, 2323);
        if (!m_pTcpSocket->waitForConnected(1000)) {
            QMessageBox::information(this, "Подключение к серверу", "Не удалось подключиться к серверу!");
        }
    }
}

//Вывод информации о пользователе (или скрыть)
void pc_resources::on_action_UserInfo_triggered()
{
    if(ui->groupBox -> isVisible()) {
        ui -> groupBox -> hide();
    } else {
        ui -> groupBox -> show();
    }
}

// Картинки ----------------------------------------------------------------

void pc_resources::getImage(int sel) {
    QPixmap pix;
    switch (sel) {
    case 1:
        pix.load(":/resources/img/pngwing.com.png");
        break;
    case 2:
        pix.load(":/resources/img/pngwing.com (1).png");
        break;
    case 3:
        pix.load(":/resources/img/pngwing.com (2).png");
        break;
    case 4:
        pix.load(":/resources/img/pngwing.com (3).png");
        break;
    default: pix.load(":/resources/img/pngwing.com.png");
    }
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}

void pc_resources::on_action_Image_PC_triggered()
{
    getImage(1);
}


void pc_resources::on_action_Image_Printer_triggered()
{
    getImage(2);
}


void pc_resources::on_action_Image_Laptop_triggered()
{
    getImage(3);
}


void pc_resources::on_action_Image_Server_triggered()
{
    getImage(4);
}
// Картинки ----------------------------------------------------------------
