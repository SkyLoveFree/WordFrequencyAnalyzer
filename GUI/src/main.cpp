#include <QApplication>

#include"Mymainwindow.h"

int main(int argc,char*argv[])
{
    qDebug()<<"hello skyreader";

    QApplication app(argc,argv);

    MyMainWindow mainwindow;

    mainwindow.show();


    return app.exec();
}