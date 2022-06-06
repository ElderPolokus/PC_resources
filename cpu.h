#ifndef CPU_H
#define CPU_H
#include <QProcess>

class cpu {
public:
    cpu();
    QString cpu_value;
private:
    QProcess *process;
};

#endif // CPU_H
