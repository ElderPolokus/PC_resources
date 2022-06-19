#include "disk.h"
#include <QStorageInfo>
#include <windows.h>

disk::disk() {
    QStorageInfo storage = QStorageInfo::root();
    name_disk = (QString("Диск (") + (storage.rootPath().left(2)) + QString(") ") + storage.name());
    disk_value_int = storage.bytesAvailable()*100/storage.bytesTotal();
}
