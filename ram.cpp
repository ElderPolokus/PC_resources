#include "ram.h"
#include <QRegularExpression>
#include <QProcess>
#include <QDebug>

ram::ram() {
    QProcess process;
    float TPM;    //TotalPhysicalMemory
    float FPM;    //FreePhysicalMemory
    QString p_reader;
    QRegularExpression re("\\D");

    process.start("cmd.exe", QStringList() << "/c" << "wmic OS get FreePhysicalMemory");
    process.waitForReadyRead();
    p_reader = process.readAll();
    process.close();
    p_reader.remove(re);
    FPM = p_reader.toInt()/1024;

    process.start("cmd.exe", QStringList() << "/c" << "wmic ComputerSystem get TotalPhysicalMemory");
    process.waitForReadyRead();
    p_reader = process.readAll();
    process.close();
    p_reader.remove(re);
    TPM = p_reader.toLongLong()/(1024*1024);
    FPM = 100-(FPM*100/TPM);
    ram_value = QString::number(round(FPM));
}
