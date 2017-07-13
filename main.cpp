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



    qDebug() << "UID: " << tv->getOwnerUid(8413);
    tv->getUsername(tv->getOwnerUid(8413));
    tv->getProcessData(QString::number(8413));
    tv->getMemoryUsage();
    tv->getProcs();
    tv->getCpuUsage();
    tv->getProcs();


    return a.exec();
}
