#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>
#include "include/qextserialbase.h"
#include "include/win_qextserialport.h"

enum protocal_type {
    SERIAL,
    GPIB,
    ETHERNET,
};

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QString com,PortSettings portsettings, QObject *parent = 0);
    ~MyThread();


    void run();
    void stopThread();

public:
    PortSettings portsettings;
    QString msg;
    bool write;

signals:
    void serialFinished(QByteArray tempR);

private:
    //QMutex mutex;
    Win_QextSerialPort *myCom;//声明对象
    bool stopped;
    bool locked;

};

#endif // MYTHREAD_H
