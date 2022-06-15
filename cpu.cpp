#include "cpu.h"
#include <windows.h>
#include <QDebug>

ULONGLONG cpu::filetime(FILETIME &ft) {
    ULARGE_INTEGER ul;
    ul.HighPart = ft.dwHighDateTime;
    ul.LowPart = ft.dwLowDateTime;
    return ul.QuadPart;
}

cpu::cpu() {
    FILETIME idle, prev_idle;
    FILETIME kernel, prev_kernel;
    FILETIME user, prev_user;
    GetSystemTimes(&prev_idle, &prev_kernel, &prev_user);
    Sleep(1000);
    GetSystemTimes(&idle, &kernel, &user);
    ULONGLONG sys = (ft2ull(user) - ft2ull(prev_user)) + (ft2ull(kernel) - ft2ull(prev_kernel));
    int cpu = int((sys - ft2ull(idle) + ft2ull(prev_idle)) * 100.0 / sys);
    prev_idle = idle;
    prev_kernel = kernel;
    prev_user = user;
    cpu_value = QString::number(cpu);
    cpu_value_int = cpu;
}
