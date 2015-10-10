#include "mythread.h"
#include <QVector>
#include <QtAlgorithms>

MyThread::MyThread(QString com, PortSettings portsettings, QObject *parent) :
    QThread(parent)
{
    myCom = new Win_QextSerialPort(com, QextSerialBase::EventDriven);
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    myCom->open(QIODevice::ReadWrite);//以可读方式打开串口
    myCom->setBaudRate(portsettings.BaudRate);
    myCom->setDataBits(portsettings.DataBits);
    myCom->setParity(portsettings.Parity);
    myCom->setStopBits(portsettings.StopBits);
    myCom->setFlowControl(portsettings.FlowControl);//设置数据流控制，我们使用无数据流控制的默认设置
    myCom->setTimeout(portsettings.Timeout_Millisec);//设置延时

    read = false;
    write = false;
    stopped = false;

    myCom->write(QByteArray("*RST\r\n"));
    /*
    myCom->write(QByteArray(":SOUR:FUNC VOLT\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:MODE FIXED\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:RANG 200\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:LEV 0\r\n"));
    myCom->write(QByteArray(":SENS:CURR:PROT 10E-5\r\n"));

    myCom->write(QByteArray(":SENS:FUNC \"CURR\"\r\n"));
    myCom->write(QByteArray(":SENS:CURR:RANG 10E-5\r\n"));
    myCom->write(QByteArray(":OUTP ON\r\n"));
    */
}

MyThread::~MyThread()
{
    myCom->write(QByteArray("*RST\r\n"));
    myCom->write(QByteArray("*CLS\r\n"));
    //myCom->write(QByteArray("*SRE 0\r\n"));
    myCom->close();//关闭串口，该函数在win_qextserialport.cpp文件中定义
}

void MyThread::run()
{
    locked = true;
    while(!stopped)
    {
        if(write)
        {
            write = false;
            myCom->write(msg.toLatin1());
            read = true;
        }

        msleep(1000);

        QByteArray tempR = myCom->readAll();
        if(!tempR.isEmpty())
        {
            emit this->serialFinished(tempR);
        }

        if(read)
            myCom->write(QByteArray(":READ?\r\n"));
    }
    locked = false;
}

void MyThread::stopThread()
{
    stopped = true;
    while(locked)
        msleep(50);
}


