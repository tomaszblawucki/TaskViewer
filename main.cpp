#include <QCoreApplication>
#include "taskviewer.h"
#include <unistd.h>
#include <QDebug>
#include <QDirIterator>
#include <QRegExp>
#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TaskViewer *tv = new TaskViewer();

    tv->renderView();
    return a.exec();
}
