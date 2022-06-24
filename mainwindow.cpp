#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpu.h"
#include "ram.h"
#include "disk.h"
#include "userinfo.h"
#include <QTimer>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    //GroupBox
    ui -> groupBox -> hide();
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
    } else {
        ui -> pB_RAM -> setValue(ram.ram_value_int);
    }

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

void MainWindow::on_action_UserInfo_triggered()
{
    if(ui->groupBox -> isVisible()) {
        ui -> groupBox -> hide();
    } else {
        ui -> groupBox -> show();
    }
}
