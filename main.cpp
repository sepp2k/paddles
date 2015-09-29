#include <QApplication>
#include "mainwindow.h"
#include <stdlib.h>
#include <time.h>



int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow win;
    win.show();
    win.setFixedSize(win.size());

    return a.exec();
}
