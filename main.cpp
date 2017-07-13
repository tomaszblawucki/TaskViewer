#include <QCoreApplication>
#include "taskviewer.h"
#include <unistd.h>
#include <QDebug>
#include <QDirIterator>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TaskViewer *tv = new TaskViewer();



    qDebug() << "UID: " << tv->getOwnerUid(1863);
    tv->getUsername(tv->getOwnerUid(1863));
    tv->getProcessData(QString::number(1863));
    tv->getMemoryUsage();
    //tv->getCpuUsage();
    QDirIterator it("/proc");
    QString dirNum;

    while (it.hasNext())
    {

        dirNum = it.next();
        if( !QString::number(QString::toInt(dirNum.split('/')[2])).isNull() )
        qDebug() <<dirNum.split('/')[2];
    }

    return a.exec();
}
