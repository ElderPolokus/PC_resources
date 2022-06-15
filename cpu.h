#ifndef CPU_H
#define CPU_H
#include <QString>
#include <windows.h>

class cpu {
public:
    cpu();
//    ~cpu();
    QString cpu_value;
    int cpu_value_int;
    static ULONGLONG filetime(FILETIME &ft);
};

#endif // CPU_H
