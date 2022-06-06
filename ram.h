#ifndef RAM_H
#define RAM_H
#include <QProcess>

class ram {
public:
    ram();
    QString ram_value;
private:
    QProcess *process;
};

#endif // RAM_H
