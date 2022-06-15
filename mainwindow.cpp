#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpu.h"
#include "ram.h"
#include <QTimer>
#include <QPixmap>

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
    ui -> progressBar_2 -> setValue(ram.ram_value_int);
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

