#include "ram.h"
#include <QDebug>
#include <windows.h>
#include <QMessageBox>

ram::ram() {
    MEMORYSTATUSEX memory_status;
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memory_status)) {
      ram_value_int = memory_status.dwMemoryLoad;
    } else {
        err = "Ошибка в выводе информации по ОЗУ";
    }
}
