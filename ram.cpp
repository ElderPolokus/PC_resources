#include "ram.h"
#include <QDebug>
#include <windows.h>

ram::ram() {
    MEMORYSTATUSEX memory_status;
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memory_status)) {
//      ram_value = (QString("%1 %").arg(memory_status.dwMemoryLoad));
      ram_value_int = memory_status.dwMemoryLoad;
    } else {
//      ram_value = ("Unknown RAM");
    }
}
