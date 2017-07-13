#include <QFile>
#include <QList>
#include <QTime>
#include <QDebug>
#include <QTextStream>

#ifndef TASKVIEWER_H
#define TASKVIEWER_H


class TaskViewer
{
private:

    QString username;//ok
    QString processName;
    QString processState;
    QString processPid;


    double cpuLoad;
    double processLoadShare;

    double memUsage;
    double processmemUsage;



public:
    TaskViewer();
    QString getOwnerUid(int pid);//ok
    void getUsername(QString uid);//ok
    void getProcessData(QString pid);
    void getCpuUsage();//ok?? bugi
    void getMemoryUsage();
    void getProcessMemoryUsage(QString pid);





};

#endif // TASKVIEWER_H
