#include <QCoreApplication>
#include "taskviewer.h"
#include <unistd.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TaskViewer *tv = new TaskViewer();

    tv->getCpuUsage();
    tv->getOwnerUid(1863);
    tv->getUsername(tv->getOwnerUid(1863));
    tv->getProcessData(QString::number(1860));
    return a.exec();
}
