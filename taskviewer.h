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
    QString processName;
    QString processState;
    QString processPid;
    QStringList procDirs;


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
    void getMemoryUsage();//ok
    void getProcessMemoryUsage(QString pid);

    void getProcs();




};

#endif // TASKVIEWER_H
