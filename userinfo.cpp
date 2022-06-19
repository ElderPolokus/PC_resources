#include "userinfo.h"
#include <windows.h>
#include <lmcons.h>
#include <QNetworkInterface>
#include <sysinfoapi.h>

UserInfo::UserInfo() {
    //Имя пользователя
    //UNLEN+1 нужен, чтобы избежать переполнение буфера.
    char buf[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserNameA(buf, &username_len);
    UserName = buf;

    //IP-адрес
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
             IP_address += address.toString() + "\n                    ";
        }
    }

    //Время работы ПК
    long long milliseconds = GetTickCount64();
    long long days = milliseconds/86400000;
    long long hours = (milliseconds - (86400000*days))/3600000;
    long long minutes = (milliseconds - (86400000*days) - (hours*3600000))/60000;
    long long seconds = (milliseconds - (86400000*days) - (hours*3600000) - (minutes*60000))/1000;
    PC_time = QString("\nДней: %1\nЧасов: %2\nМинут: %3\nСекунд: %4").arg(days).arg(hours).arg(minutes).arg(seconds);
}
