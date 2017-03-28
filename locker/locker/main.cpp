#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include"configs.h"
QString ip="192.168.1.109";

#include"MyLock.h"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

   // getfile();
    init();
    //openLock();
setPowerPin23();
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("智能快递管家");
    w.show();
    
    return a.exec();
}
