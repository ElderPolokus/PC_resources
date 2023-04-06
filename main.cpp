#include "pc_resources.h"
#include <QNetworkInterface>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pc_resources pc_res;
    pc_res.show();
    return a.exec();
}
