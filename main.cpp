#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    //使程序可处理中文
    MainWindow w;
    w.show();

    return a.exec();
}
