#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuFunction->setDisabled(true);

    //初始化成员变量
    mythread = NULL;

    //连接信号与槽
    connect(& serialdialog,SIGNAL(Serial_connect()),this,SLOT(SerialDialog_PB_connect_clicked()));
    connect(& serialdialog,SIGNAL(Serial_close()),this,SLOT(SerialDialog_PB_close_clicked()));
    connect(& biasdialog,SIGNAL(Bias_Update()),this,SLOT(BiasDialog_PB_BiasUpdate_clicked()));

}

MainWindow::~MainWindow()
{
    if(mythread!=NULL)
    {
        mythread->stopThread();
        delete mythread;
        mythread = NULL;
    }
    delete ui;
}

void MainWindow::dataReceive(QByteArray data)
{
    ui->lcdNumber_2->display(QString(data));
}


void MainWindow::on_actionAbout_triggered()
{
    aboutdialog.setModal(true);
    aboutdialog.show();
}

void MainWindow::on_actionSerial_triggered()
{
    serialdialog.setModal(true);
    serialdialog.show();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication * app;
    app->exit(0);
}

void MainWindow::on_actionModel_triggered()
{
    modeldialog.setModal(true);
    modeldialog.show();
}

void MainWindow::on_actionBias_Set_triggered()
{
    biasdialog.setModal(true);
    biasdialog.show();
}


void MainWindow::SerialDialog_PB_connect_clicked()
{
    ui->lcdNumber->display(serialdialog.getPort());

    mythread = new MyThread(serialdialog.getPort(), serialdialog.getPortSettings(), this);
    connect(mythread,SIGNAL(serialFinished(QByteArray)),this,SLOT(dataReceive(QByteArray)));
    mythread->start();

    //connect(mythread,SIGNAL(serialFinished(QByteArray)),this,SLOT(ReadDate(QByteArray)));

    ui->menuFunction->setDisabled(false);

}
void MainWindow::SerialDialog_PB_close_clicked()
{
    if(mythread!=NULL)
        {
            mythread->stopThread();
            delete mythread;
            mythread = NULL;
        }
    ui->menuFunction->setDisabled(true);
}

void MainWindow::BiasDialog_PB_BiasUpdate_clicked()
{
    QString bias;
    bias = QString("%1").arg(biasdialog.getBias());
    mythread->msg = ":SOUR:VOLT:IMM ";
    mythread->msg.append(bias);
    mythread->msg.append("\r\n");
    mythread->msg.append("*RST\r\n");
    mythread->msg.append(":SOUR:FUNC VOLT\r\n");
    mythread->msg.append(":SOUR:VOLT:MODE FIXED\r\n");
/*
    myCom->write(QByteArray("*RST\r\n"));

    myCom->write(QByteArray(":SOUR:FUNC VOLT\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:MODE FIXED\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:RANG 200\r\n"));
    myCom->write(QByteArray(":SOUR:VOLT:LEV 0\r\n"));
    myCom->write(QByteArray(":SENS:CURR:PROT 10E-5\r\n"));

    myCom->write(QByteArray(":SENS:FUNC \"CURR\"\r\n"));
    myCom->write(QByteArray(":SENS:CURR:RANG 10E-5\r\n"));
    myCom->write(QByteArray(":OUTP ON\r\n"));
    */

    mythread->write = true;
}
