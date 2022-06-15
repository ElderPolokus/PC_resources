#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpu.h"
#include "ram.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer()
{
    cpu cpu;
    ui -> textEdit -> setText(cpu.cpu_value + "%");
    ui -> progressBar -> setValue(cpu.cpu_value_int);
    ram ram;
    ui -> textEdit_2 -> setText(ram.ram_value);
    ui -> progressBar_2 -> setValue(ram.ram_value_int);
}

