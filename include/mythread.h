#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>
#include "qextserialbase.h"
#include "win_qextserialport.h"

typedef struct Serial_Parameter {
    QString port;
    QString baudRate;
    QString dataBits;
    QString parity;
    QString stopBits;
    QString flowControl;
    int timeOut;
}Serial_Parameter;

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QString com, QObject *parent = 0);
    ~MyThread();
    void run();
    void stopThread();
    int sendmsg;
    QString com_msg;
    int com_cmd;


signals:
    void serialFinished(QByteArray tempR);

private:
    QMutex mutex;
    Win_QextSerialPort *myCom;//声明对象
    int stopped;
    int locked;
    enum protocal_type {
        SERIAL = 0,
        GPIB,
        ETHERNET,
    };

};

#endif // MYTHREAD_H
