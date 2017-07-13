#include <QCoreApplication>
#include "taskviewer.h"
#include <unistd.h>
#include <QDebug>
#include <QDirIterator>
#include <QRegExp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TaskViewer *tv = new TaskViewer();



    qDebug() << "UID: " << tv->getOwnerUid(1863);
    tv->getUsername(tv->getOwnerUid(1863));
    tv->getProcessData(QString::number(1863));
    tv->getMemoryUsage();
    //tv->getCpuUsage();
    tv->getProcs();

    return a.exec();
}
