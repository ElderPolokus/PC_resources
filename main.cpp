#include "mainwindow.h"
#include <QNetworkInterface>
#include <QApplication>

int main(int argc, char *argv[])
{
    //IP-адрес компьютера
    QString strHost;
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
             strHost = address.toString();
        }
    }
    QApplication a(argc, argv);
    MainWindow w(strHost, 2323);
    w.show();
    return a.exec();
}
