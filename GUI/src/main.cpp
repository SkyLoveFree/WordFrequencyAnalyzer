#include"TextAnalyzer.h"
#include"SkyReader_gui_Widget.h"
#include <QApplication>

int main(int argc,char*argv[])
{
    qDebug()<<"hello skyreader";
    QApplication app(argc,argv);
    SkyReader_gui_Widget sample1;
    sample1.show();
    return app.exec();
}