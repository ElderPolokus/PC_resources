#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , process (nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString znach;
    float znach1 = 0;
    float znach2 = 0;
    QRegularExpression re("\\D");

//    QProcess* process = new QProcess(this);
//    process -> start("cmd.exe", QStringList() << "/c" << "wmic cpu get loadpercentage");
//    process -> waitForReadyRead();
//    process -> waitForFinished();
//    if (process -> exitStatus() != QProcess::NormalExit) {
//            qDebug() << "error QProcess: " << (int)process -> error();
//            qDebug() << "errorStr: " << process -> errorString();
//        } else {
//            qDebug() << "exit code:" << process -> exitCode();
//            znach = "output:" + process -> readAll();
//        }
//    ui -> textEdit -> setText(znach);


//    QProcess* process = new QProcess(this);
//    process -> start("cmd.exe", QStringList() << "/c" << "wmic OS get FreePhysicalMemory");
//    process -> waitForReadyRead();
//    process -> waitForFinished();
//    if (process -> exitStatus() != QProcess::NormalExit) {
//            qDebug() << "error QProcess: " << (int)process -> error();
//            qDebug() << "errorStr: " << process -> errorString();
//        } else {
//            qDebug() << "exit code:" << process -> exitCode();
//            znach = process -> readAll();
//            znach.remove(re);
//        }
//    ui -> textEdit -> setText(znach);


    QProcess* process = new QProcess(this);
    process -> start("cmd.exe", QStringList() << "/c" << "wmic OS get FreePhysicalMemory");
    process -> waitForReadyRead();
    znach = process -> readAll();
    process -> close();
    znach.remove(re);
    znach1 = znach.toInt()/1024;

    process -> start("cmd.exe", QStringList() << "/c" << "wmic ComputerSystem get TotalPhysicalMemory");
    process -> waitForReadyRead();
    znach = process ->readAll();
    process -> close();
    znach.remove(re);
    znach2 = znach.toLongLong()/(1024*1024);
    znach1 = 100-(znach1*100/znach2);
    znach = QString::number(round(znach1));

    ui -> textEdit -> setText(znach + "%");
}

