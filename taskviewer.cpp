#include "taskviewer.h"
#include <unistd.h>
#include <iostream>
#include <iomanip>



TaskViewer::TaskViewer()
{
    getProcs();
}

QString TaskViewer::getOwnerUid(int pid)
{
    //qDebug() <<"Started";
    QFile *file = new QFile(QString("/proc/")+QString::number(pid)+QString("/status"));
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(file);
        QString line;
        for(int i = 0; i < 7; i++)
            in.readLine();

        in >> line;
        in >> line;
        //qDebug() <<"UID: " << line;
        file->close();
        delete file;
        return line;
    }
    else
    std::cout<<"File not found"<<std::endl;


    return 0;
}

void TaskViewer::getUsername(QString uid)
{
    QFile *file = new QFile("/etc/passwd");
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {

        if(uid == QString::number(4294967295)){
            username = "not set";
            //qDebug() << "USERNAME:" <<username;
            return;
        }
        QTextStream in(file);
        QString line;
        do{
            line = in.readLine();
            if(line.contains(uid) /*&& line.split(':')[2] == uid*/)
            {
                //4294967295 is the unsigned user or root!!!
                //qDebug()<<"Found"<<line.split(':')[2];
                //qDebug()<<"USERNAME"<<line.split(':')[0];
                username = line.split(':')[0];
                return;
            }
        }while(!line.isNull());
    }
    else
     std::cout<<"File /etc/passwd not found"<<std::endl;

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
        //qDebug() <<"PID: " << processPid << "PROCESS NAME: " << processName << "PROCESS STATE: "<<processState;
        file->close();
        delete file;
        return;
    }
    else
    std::cout<<"File proc/"<<pid.toStdString()<< "/stat not found"<<std::endl;
    return;
}


void TaskViewer::getCpuUsage()
{
    QFile *file = new QFile("/proc/stat");

    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug() <<"File opened";
        QString line;
        QString values[11];
        long int total_jiffies_1 = 0;
        long int work_jiffies_1 = 0;
        long int total_jiffies_2 = 0;
        long int work_jiffies_2 = 0;

        double load = 0;


        //line = procs_stat->readLine();
        {
        QTextStream in(file);
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
        file->close();

        sleep(2);

        file->open(QIODevice::ReadOnly | QIODevice::Text);


        QTextStream in(file);
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
        file->close();
        //qDebug() <<"Total jiffies before" << total_jiffies_1;
        //qDebug() <<"Total work before" <<work_jiffies_1;
        //qDebug() <<"Total jiffies after" <<total_jiffies_2;
        //qDebug() <<"Total work after" <<work_jiffies_2;

        load = (100*(double(work_jiffies_2 - work_jiffies_1)/double(total_jiffies_2 - total_jiffies_1)));
        //qDebug() << (work_jiffies_2 - work_jiffies_1);
        //qDebug() << (total_jiffies_2 - total_jiffies_1);
        //qDebug() << "cpu load: " << load << "%";
        cpuLoad = QString::number(load, 'f', 2);
    }
    else
    {
        std::cout<<"File /proc/stat not found"<<std::endl;

    }
    delete file;
    return;
}

void TaskViewer::getMemoryUsage()
{
    QFile *file = new QFile("/proc/meminfo");
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(file);
        QString line;
        long int total, used;

        in >> line;
        in >> line;
        total = line.toDouble();
        in.readLine();
        in >> line;
        in >> line;
        memFree = line.toDouble();
        used = total - memFree;
        memUsageKb = total;
        memUsage = QString::number((100*(double(used)/double(total))), 'f', 2);
        //qDebug() << "MEMORY USAGE: " <<memUsage << "%" << " FREE: " << free << " TOTAL: " << total;

    }
    else
    qDebug() <<"File /proc/meminfo not found";
    file->close();
    delete file;
    return;
}

void TaskViewer::getProcessMemoryUsage(QString pid)
{
    QFile *file = new QFile(QString("/proc/")+pid+QString("/statm"));
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(file);
        QString line;
        long int virt, res, shr;

        in >> line;
        virt = line.toInt()*(4096/1024);
        in >> line;
        res = line.toInt()*(4096/1024);
        in >> line;
        shr = line.toInt()*(4096/1024);
        processmemUsageVirt = virt;
        processmemUsageRes = res;
        processmemUsageShr = shr;
        processmemUsage = (double(res)/double(memUsageKb))*100;
        //qDebug() << "VIRT: " << processmemUsageVirt << " RES: " << processmemUsageRes << " SHR: " << processmemUsageShr << "%MEM_US: " << processmemUsage;


    }
    else
    qDebug() <<"File /proc/"<<pid<<"/statm not found";
    file->close();
    delete file;
    return;

}

void TaskViewer::getProcs()
{
    QDirIterator it("/proc");
    QString dirNum;
    QRegExp rxp("\\d*");

    while (it.hasNext())
    {
        dirNum = it.next();
        if( rxp.exactMatch(dirNum.split('/')[2]) )
        {
            procDirs.append( dirNum.split('/')[2] );
            //qDebug() << dirNum.split('/')[2];;
        }

    }
}

void TaskViewer::showProcInline(QString pid)
{
    getProcessData(pid);
    getProcessMemoryUsage(pid);
    getUsername(getOwnerUid(pid.toInt()));

    //qDebug() <<setwidth(QString("PID"), 10) << setwidth(QString("STATE"), 10) <<  setwidth(QString("USR"), 10) << setwidth("VIRT",10) << setwidth("RES", 10) << setwidth("SHR", 10) << setwidth("%MEM", 10) << setwidth("COMMAND", 10);
//    qDebug() << "PID" << fillRest("PID", 8) << "STATE" << fillRest("STATE", 8) <<  "USR" << fillRest("USR", 5) << "VIRT"  << fillRest("VIRT", 8) << "RES" << fillRest("RES", 8) << "SHR" << fillRest("SHR", 8) << "%MEM"  << fillRest("USR", 8) << "COMMAND";
//    qDebug() << pid << fillRest(pid, 8) << processState << fillRest(processState, 8)
//             << username << fillRest(username, 5) << processmemUsageVirt << fillRest(QString::number(processmemUsageVirt), 8) <<processmemUsageRes
//             << fillRest(QString::number(processmemUsageRes), 8) << processmemUsageShr << fillRest(QString::number(processmemUsageShr), 8) << processmemUsage << fillRest(QString::number(processmemUsage), 8) << processName;


    std::cout << std::setw(10)<<std::left<< pid.toStdString()
              << std::setw(10)<<std::left<< processState.toStdString()
              << std::setw(10)<<std::left<< username.toStdString()
              << std::setw(10)<<std::left<< processmemUsageVirt
              << std::setw(10)<<std::left<< processmemUsageRes
              << std::setw(10)<<std::left<< processmemUsageShr
              << std::setw(10)<<std::left<< processmemUsage
              << std::setw(10)<<std::left<< processName.toStdString()
              << std::endl;
    return;
}

void TaskViewer::renderView()
{

    getProcs();
    getMemoryUsage();
    getCpuUsage();
    std::cout <<"%CPU: "<<cpuLoad.toStdString()<<"%  "
              <<" MEM TOTAL(KB): "  << memUsageKb
              <<" MEM FREE(KB): "  << memFree
              <<" MEM_USED(%): "<<memUsage.toStdString()<<"%"
              <<std::endl;


    std::cout << std::setw(10)<<std::left<< "PID"
              << std::setw(10)<<std::left<< "STATE"
              << std::setw(10)<<std::left<<  "USR"
              << std::setw(10)<<std::left<< "VIRT"
              << std::setw(10)<<std::left<< "RES"
              << std::setw(10)<<std::left<< "SHR"
              << std::setw(10)<<std::left<< "%MEM"
              << std::setw(10)<<std::left<< "COMMAND"
              << std::endl;

    for(int i = 0; i < (procDirs.size()/2); ++i)
        showProcInline(procDirs[i]);

}
