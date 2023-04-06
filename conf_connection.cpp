#include "conf_connection.h"
#include "ui_conf_connection.h"
#include <QMessageBox>
#include <QFile>
#include <QtXml>
#include <QDebug>
#include <QRegularExpression>

conf_connection::conf_connection(QString send_IP, int send_Port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::conf_connection)
{
    ui->setupUi(this);
    //Порт используемый на данный момент
    Port = send_Port;
    IP = send_IP;
    ui->lineEdit->setPlaceholderText("Порт: " + QString::number(send_Port));
    ui->lineEdit_2->setPlaceholderText("IP: " + send_IP);
}

conf_connection::~conf_connection()
{
    delete ui;
}

void conf_connection::on_Accept_clicked()
{
    QString message;
    int ch_Port = Port;
    QString ch_IP = IP;
    //Порт из диалогового окна
    if(!(ui->lineEdit->text()).isEmpty()) {
        int ch_Port_switch = (ui->lineEdit->text()).toInt();
        switch (ch_Port_switch) {
        case 874 ... 5799: {
            ch_Port = (ui->lineEdit->text()).toInt();
            slotChangeConfigConnectPort(ch_Port);
            break;
        }
        case 1 ... 873:
            message = "Введите номер порта от 874 до 5799";
            break;
        case 5800 ... 9999:
            message = "Введите номер порта от 874 до 5799";
            break;
        default:
            message = "Введите номер порта без лишних символов начиная с 874";
        }
    }

    QRegularExpression regIPv4("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");

    if(!(ui->lineEdit_2->text()).isEmpty()) {
        if(regIPv4.match(ui->lineEdit_2->text()).hasMatch()) {
            ch_IP = ui->lineEdit_2->text();
            slotChangeConfigConnectIP(ch_IP);
        } else {
            message = "\n введите корректный IP";
        }
    }
    if(message != "") {
        QMessageBox::critical(this, "Ошибка", message);
    }
    if(ch_IP != IP || ch_Port != Port) {
        emit sendConfig(ch_IP, ch_Port);
        close();
    }
}

void conf_connection::on_Escape_clicked()
{
    close();
}

void conf_connection::slotChangeConfigConnectPort(int ch_Port)
{
    QDomDocument doc;
    QFile file(".configConnect.xml");
    if(file.open(QIODevice::ReadOnly)) {
        doc.setContent(&file);
        file.close();
    }

    QDomElement nodeTag;

    QDomElement documentTag = doc.documentElement();
    if(documentTag.isNull()) {
        QDomElement documentTag = doc.createElement("Configurations");
        doc.appendChild(documentTag);
        nodeTag = doc.createElement("ConfigPort");
        nodeTag.setAttribute("Port", ch_Port);
        documentTag.appendChild(nodeTag);
    } else {
        nodeTag = documentTag.firstChildElement("ConfigPort");
        if(nodeTag.isNull()) {
            nodeTag = doc.createElement("ConfigPort");
            nodeTag.setAttribute("Port", ch_Port);
            documentTag.appendChild(nodeTag);
        } else {
            nodeTag.setAttribute("Port", ch_Port);
        }
    }

    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
}

void conf_connection::slotChangeConfigConnectIP(QString ch_IP)
{
    QDomDocument doc;
    QFile file(".configConnect.xml");
    if(file.open(QIODevice::ReadOnly)) {
        doc.setContent(&file);
        file.close();
    }

    QDomElement nodeTag;

    QDomElement documentTag = doc.documentElement();
    if(documentTag.isNull()) {
        QDomElement documentTag = doc.createElement("Configurations");
        doc.appendChild(documentTag);
        nodeTag = doc.createElement("ConfigIP");
        nodeTag.setAttribute("IP", ch_IP);
        documentTag.appendChild(nodeTag);
    } else {
        nodeTag = documentTag.firstChildElement("ConfigIP");
        if(nodeTag.isNull()) {
            nodeTag = doc.createElement("ConfigIP");
            nodeTag.setAttribute("IP", ch_IP);
            documentTag.appendChild(nodeTag);
        } else {
            nodeTag.setAttribute("IP", ch_IP);
        }
    }

    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
}
