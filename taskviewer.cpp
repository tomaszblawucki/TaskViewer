#include "taskviewer.h"
#include <unistd.h>

TaskViewer::TaskViewer()
{

}

QString TaskViewer::getOwnerUid(int pid)
{
    //qDebug() <<"Started";
    QFile *file = new QFile(QString("/proc/")+QString::number(pid)+QString("/loginuid"));
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(file);
        QString line;
        in >>line;
        //qDebug() <<"UID: " << line;
        file->close();
        delete file;
        return line;
    }
    else
    qDebug() <<"File not found";


    return 0;
}

void TaskViewer::getUsername(QString uid)
{
    QFile *file = new QFile("/etc/passwd");
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(file);
        QString line;
        do{
            line = in.readLine();
            if(line.contains(uid) && line.split(':')[2] == uid)
            {

                //qDebug()<<"Found"<<line.split(':')[2];
                qDebug()<<"Username"<<line.split(':')[0];
                username = line.split(':')[0];
                return;
            }
        }while(!line.isNull());
    }
    else
    qDebug() <<"File not found";

    return;

}

void TaskViewer::getProcessData(QString pid)
{
    QFile *file = new QFile(QString("/proc/")+pid+QString("/stat"));
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(file);
        QString line;
        in >>processPid;
        in >>processName;
        in >>processState;
        qDebug() <<"PID: " << processPid << "PROCESS NAME: " << processName << "PROCESS STATE: "<<processState;
        file->close();
        delete file;
        return;
    }
    else
    qDebug() <<"File not found";
    return;
}


void TaskViewer::getCpuUsage()
{
    QFile *procs_stat = new QFile("/proc/stat");

    if(procs_stat->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug() <<"File opened";
        QString line;
        QString values[10];
        long int total_jiffies_1 = 0;
        long int work_jiffies_1 = 0;
        long int total_jiffies_2 = 0;
        long int work_jiffies_2 = 0;

        double load = 0;


        //line = procs_stat->readLine();
        {
        QTextStream in(procs_stat);
        for(int i =0; i<11; i++)
        {
            in >> values[i];
            //qDebug() << values[i];
        }
        for(int i =0; i < 11; i++)
        {
            total_jiffies_1 += values[i].toDouble();
            if(i < 3)
                work_jiffies_1 += values[i].toDouble();
        }
        }
        procs_stat->close();

        sleep(2);

        procs_stat->open(QIODevice::ReadOnly | QIODevice::Text);


        QTextStream in(procs_stat);
        {
        for(int i =0; i<11; i++)
            {
                in >> values[i];
               // qDebug() << values[i];
            }
        for(int i =0; i < 11; i++)
            {
                total_jiffies_2 += values[i].toDouble();
                if(i < 3)
                    work_jiffies_2 += values[i].toDouble();
            }
        }
        procs_stat->close();
        //qDebug() <<"Total jiffies before" << total_jiffies_1;
        //qDebug() <<"Total work before" <<work_jiffies_1;
        //qDebug() <<"Total jiffies after" <<total_jiffies_2;
        //qDebug() <<"Total work after" <<work_jiffies_2;

        load = (100*(double(work_jiffies_2 - work_jiffies_1)/double(total_jiffies_2 - total_jiffies_1)));
        //qDebug() << (work_jiffies_2 - work_jiffies_1);
        //qDebug() << (total_jiffies_2 - total_jiffies_1);
        qDebug() << "cpu load: " << load << "%";

    }
    else
    {
        qDebug() <<"File '/proc/stat' open fail!!";

    }
    delete procs_stat;
    return;
}