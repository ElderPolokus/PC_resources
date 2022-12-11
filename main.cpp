#include "pc_resources.h"
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
    pc_resources pc_res(strHost, 2323);
    pc_res.show();
    return a.exec();
}
