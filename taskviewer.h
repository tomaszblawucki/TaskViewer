#include <QFile>
#include <QList>
#include <QTime>
#include <QDebug>
#include <QTextStream>
#include <QDirIterator>
#include <QRegExp>
#include <QStringList>

#ifndef TASKVIEWER_H
#define TASKVIEWER_H


class TaskViewer
{
private:

    QString username;//ok
    QString processName;//ok
    QString processState;//ok
    QString processPid;//ok
    QStringList procDirs;//ok


    double cpuLoad;//ok
    double processLoadShare;//TO_DO

    double memUsage;//ok
    double processmemUsage;//TO_DO



public:
    TaskViewer();
    QString getOwnerUid(int pid);//ok
    void getUsername(QString uid);//ok
    void getProcessData(QString pid);
    void getCpuUsage();//ok
    void getMemoryUsage();//ok
    void getProcessMemoryUsage(QString pid);//TO_DO
    void getProcs();




};

#endif // TASKVIEWER_H
