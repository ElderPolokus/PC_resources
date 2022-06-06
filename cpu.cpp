#include "cpu.h"
#include <QRegularExpression>
#include <QProcess>
#include <QDebug>

cpu::cpu() {
    QProcess process;
    QRegularExpression re("\\D");

    process.start("cmd.exe", QStringList() << "/c" << "wmic cpu get loadpercentage");
    process.waitForReadyRead();
    cpu_value = process.readAll();
    process.close();
    cpu_value.remove(re);
//    if (process.exitStatus() != QProcess::NormalExit) {
//        qDebug() << "error QProcess: " << (int)process.error();
//        qDebug() << "errorStr: " << process.errorString();
//    } else {
//        qDebug() << "exit code:" << process.exitCode();
//        cpu_value = "output:" + process.readAll();
//        cpu_value.remove(re);
//    }
}
