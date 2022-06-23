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
    ui -> progressBar -> setValue(cpu.cpu_value_int);

    ram ram;
    if(ram.err != "") {
        if((QMessageBox::critical(this, "Ошибка", ram.err, QMessageBox::Ok)) == QMessageBox::Ok) {
            qApp->exit();
        }
    } else {
        ui -> progressBar_2 -> setValue(ram.ram_value_int);
    }

    disk disk;
    ui -> label_3 -> setText(disk.name_disk);
    ui -> progressBar_3 -> setValue(disk.disk_value_int);

    UserInfo userinfo;
    QString message;
    if(userinfo.IP_address != "") {
        message = "Имя: " + userinfo.UserName + "\nIP-адреса: " + userinfo.IP_address;
    } else {
        message = "Имя: " + userinfo.UserName + "\nНе возможно получить IP-адрес";
    }
    message += "\nВремя работы ПК" + userinfo.PC_time;
    ui ->  label_4 -> setText("Информация о пользователе!\n" + message);
}

void MainWindow::on_action_2_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com.png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}


void MainWindow::on_action_3_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com (1).png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}


void MainWindow::on_action_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com (2).png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}


void MainWindow::on_action_4_triggered()
{
    QPixmap pix(":/resources/img/pngwing.com (3).png");
    width = ui -> image -> width();
    height = ui -> image -> height();
    ui -> image -> setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}

void MainWindow::on_action_5_triggered()
{
    if(ui->groupBox -> isVisible()) {
        ui -> groupBox -> hide();
    } else {
        ui -> groupBox -> show();
    }
}
