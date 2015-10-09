#include "mythread.h"
#include <QVector>
#include <QtAlgorithms>

MyThread::MyThread(QString com, QObject *parent) :
    QThread(parent)
{
    myCom = new Win_QextSerialPort(com, QextSerialBase::EventDriven);
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    myCom->open(QIODevice::ReadWrite);//以可读方式打开串口
    myCom->setBaudRate(BAUD9600);
    myCom->setDataBits(DATA_8);
    myCom->setParity(PAR_NONE);
    myCom->setStopBits(STOP_1);
    myCom->setFlowControl(FLOW_OFF);//设置数据流控制，我们使用无数据流控制的默认设置
    myCom->setTimeout(100);//设置延时


    stopped = 1;
    sendmsg = 0;
    myCom->write(QByteArray("*RST\r\n"));
    myCom->write(QByteArray(":SOUR:FUNC VOLT\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:MODE FIXED\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:RANG 200\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:LEV 0\r\n"));
    myCom->write(QByteArray(":SENS:CURR:PROT 10E-5\r\n"));

    myCom->write(QByteArray(":SENS:FUNC \"CURR\"\r\n"));
    myCom->write(QByteArray(":SENS:CURR:RANG 10E-5\r\n"));
    myCom->write(QByteArray(":OUTP ON\r\n"));
    myCom->write(QByteArray(":READ?\r\n"));
}

MyThread::~MyThread()
{
    myCom->write(QByteArray("*RST\r\n"));
    myCom->write(QByteArray("*CLS\r\n"));
    myCom->write(QByteArray("*SRE 0\r\n"));
    myCom->close();//关闭串口，该函数在win_qextserialport.cpp文件中定义
}

void MyThread::run()
{
    locked = 1;
    while(stopped)
    {
        msleep(200);

 /*       QByteArray temp = myCom->readAll();
        myCom2->write(temp);

        //temp.resize(5);
        //temp[0] = 0x83;
        //temp[1] = 0xab;
        //temp[2] = 0xff;
        //temp[3] = 0x3f;
        //temp[4] = 0x43;

        emit this->serialFinished(temperFilter(temp));

        QByteArray temp2 = myCom2->readAll();
        //读取串口缓冲区的所有数据给临时变量temp
        myCom->write(temp2);
*/
       QByteArray tempR = myCom->readAll();
       emit this->serialFinished(tempR);

       QString temp;

       if(com_cmd == 1)
       {
           temp = ":SOUR:VOLT:IMM ";
           temp.append(com_msg);
           temp.append("\r\n");
       }

       if(com_cmd == 2)
       {
           temp = com_msg;
       }

       if(sendmsg)
        {
            sendmsg = 0;
            myCom->write(temp.toLatin1());
        }

    }
    locked = 0;
}

void MyThread::stopThread()
{
    stopped = 0;
    while(locked)
        msleep(50);
}


