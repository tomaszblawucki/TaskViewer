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


    double cpuLoad;//ok
    double processLoadShare;//TO_DO


    double memUsage;//ok
    long int memUsageKb;//ok
    double processmemUsage;//ok
    long int processmemUsageVirt;//ok
    long int processmemUsageRes;//ok
    long int processmemUsageShr;//ok




public:

    QStringList procDirs;//ok

    TaskViewer();
    QString getOwnerUid(int pid);//ok
    void getUsername(QString uid);//ok
    void getProcessData(QString pid);
    void getCpuUsage();//ok
    void getMemoryUsage();//ok
    void getProcessMemoryUsage(QString pid);//ok
    void getProcs();//ok
    QString showProcInline(QString pid);
    void renderView();
    char* fillRest(QString w, int l);

};

#endif // TASKVIEWER_H
