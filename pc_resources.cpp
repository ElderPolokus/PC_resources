#include "pc_resources.h"
#include "ui_pc_resources.h"
#include "cpu.h"
#include "ram.h"
#include "disk.h"
#include "userinfo.h"
#include "conf_connection.h"
#include <QTime>
#include <QTimer>
#include <QPixmap>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QFile>
#include <QtXml>

pc_resources::pc_resources(QWidget *parent)
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
    ui -> label_status -> setText("Статус подключения: \u274c");

    //default IP
    IP = getIPHost();

    //Файл с сохраненными настройками порта и IP
    QDomDocument doc;
    QFile file(".configConnect.xml");
    if(file.open(QIODevice::ReadOnly)) {
        doc.setContent(&file);
        if(!(doc.documentElement().firstChildElement("ConfigPort")).isNull()) {
            Port = (doc.documentElement().firstChildElement("ConfigPort").attribute("Port")).toInt();
        }
        if(!(doc.documentElement().firstChildElement("ConfigIP")).isNull()) {
            IP = (doc.documentElement().firstChildElement("ConfigIP").attribute("IP"));
        }
        file.close();
    }

    //Подключение к серверу
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(IP, Port);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(disconnected()), SLOT(slotDisconnected()));
}

pc_resources::~pc_resources()
{
    delete ui;
}

void pc_resources::timer()
{
    cpu cpu;
    cpu_res = cpu.cpu_value_int;
    ram ram;
    if(ram.err != "") {
        if((QMessageBox::critical(this, "Ошибка", ram.err, QMessageBox::Ok)) == QMessageBox::Ok) {
            qApp->exit();
        }
    }
    ram_res = ram.ram_value_int;
    disk disk;
    disk_name = disk.name_disk;
    disk_res = disk.disk_value_int;

    ui -> pB_CPU -> setValue(cpu_res);
    ui -> pB_RAM -> setValue(ram_res);
    ui -> label_DISK -> setText(disk_name);
    ui -> pB_DISK -> setValue(disk_res);

    //UserInfo
    UserInfo userinfo;
    ui ->  label_Name -> setText("Имя: " + userinfo.UserName);
    if(userinfo.IP_address != "") {
        ui -> label_IP_address -> setText("\nIP-адрес: " + userinfo.IP_address);
    } else {
        ui -> label_IP_address -> setText("\nНе возможно получить IP-адрес");
    }
    ui ->  label_PC_time -> setText("\nВремя работы ПК" + userinfo.PC_time);
    //Отправка данных
    if(m_pTcpSocket->state() == QTcpSocket::ConnectedState) {
        slotSendToServer();
    }
}

void pc_resources::slotConnected() {
    QMessageBox::information(this, "Подключение к серверу", "Соединение установлено!");
    ui -> action_ConnectToServer -> setText("Отключиться от сервера");
    ui -> label_status -> setText("Статус подключения: \u2705");
}

void pc_resources::slotDisconnected() {
    QMessageBox::information(this, "Отсоединение от сервера", "Вы успешно отсоединились!");
    ui -> action_ConnectToServer -> setText("Подключиться к серверу");
    ui -> label_status -> setText("Статус подключения: \u274c");
}

QString pc_resources::getIPHost() {
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
             return address.toString();
        }
    }
    return 0;
}

void pc_resources::slotSendToServer() {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out << quint16(0) << IP << cpu_res << ram_res << disk_name << disk_res;
    out.device()->seek(0);
    out <<quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

//Подключиться к серверу (кнопка)
void pc_resources::on_action_ConnectToServer_triggered()
{
    if(m_pTcpSocket->state() == QTcpSocket::ConnectedState) {
        m_pTcpSocket->disconnectFromHost();
    } else {
        m_pTcpSocket->connectToHost(IP, Port);
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

void pc_resources::getConfigChange(QString ch_IP, int ch_port) {
    Port = ch_port;
    IP = ch_IP;
    if(m_pTcpSocket->state() == QTcpSocket::ConnectedState) {
        m_pTcpSocket->disconnectFromHost();
        m_pTcpSocket->connectToHost(IP, Port);
    } else {
        m_pTcpSocket->connectToHost(IP, Port);
    }
}

void pc_resources::on_Configure_connection_triggered()
{
    conf_connection *conf_conn = new conf_connection(IP, Port);
    connect(conf_conn,SIGNAL(sendConfig(QString,int)),this,SLOT(getConfigChange(QString,int)));
    conf_conn->exec();
}

