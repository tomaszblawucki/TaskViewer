#include <QCoreApplication>
#include "taskviewer.h"
#include <unistd.h>
#include <QDebug>
#include <QDirIterator>
#include <QRegExp>
#include <iomanip>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TaskViewer *tv = new TaskViewer();



    tv->getMemoryUsage();
    tv->getCpuUsage();
    tv->getProcs();
    tv->getUsername(tv->getOwnerUid(1863));
    tv->getProcessData(QString::number(1863));
    tv->getProcessMemoryUsage(QString::number(1863));


    tv->showProcInline(QString::number(1863));


    return a.exec();
}
