#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

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
    QByteArray voltage,current,resistance,time,status;// Raw data
    voltage = data.left(13);
    data.remove(0,14);
    current = data.left(13);
    data.remove(0,14);
    resistance = data.left(13);
    data.remove(0,14);
    time = data.left(13);
    data.remove(0,14);
    status = data.left(13);

    Number voltageTR,currentTR,resistanceTR,timeTR,statusTR;//Transferred data
    voltageTR = dataTransfer(voltage);
    currentTR = dataTransfer(current);
    resistanceTR = dataTransfer(resistance);


    if(voltageTR.simple)
    {
        ui->L_voltage->setText(voltageTR.numbersimple.c);
        ui->LCD_voltage->display(QString("%1").arg(voltageTR.numbersimple.base,0,'f',3));
    }
    else
    {
        float number;
        number = voltageTR.exponent.base * pow(10.0,voltageTR.exponent.power);
        ui->L_voltage->setText(" ");
        ui->LCD_voltage->display(QString("%1").arg(number,0,'E',2));
    }

    ui->L_current->setText(currentTR.numbersimple.c);
    ui->LCD_current->display(QString("%1").arg(currentTR.numbersimple.base,0,'f',3));

}

Number MainWindow::dataTransfer(QByteArray data)
{
    Number dataTR;
    bool ok;

    dataTR.exponent.power = data.right(3).toInt(&ok, 10);
    data.remove(9,4);
    dataTR.exponent.base = data.left(9).toFloat(&ok);

    if(dataTR.exponent.power>=-18 && dataTR.exponent.power <15)
    {
        dataTR.simple = true;
        int quotient, remainder; // 商 , 余数
        int powerTMP;// 临时变量,取决于dataTR.exponent.power的正负
        if(dataTR.exponent.power >= 0)
            powerTMP = dataTR.exponent.power;
        else
            powerTMP = dataTR.exponent.power - 2;

        quotient = powerTMP / 3;
        remainder = powerTMP % 3;
        switch(quotient)
        {
            case -6:
                dataTR.numbersimple.c = "a"; break;
            case -5:
                dataTR.numbersimple.c = "f"; break;
            case -4:
                dataTR.numbersimple.c = "p"; break;
            case -3:
                dataTR.numbersimple.c = "n"; break;
            case -2:
                dataTR.numbersimple.c = "u"; break;
            case -1:
                dataTR.numbersimple.c = "m"; break;
            case 0:
                dataTR.numbersimple.c = " "; break;
            case 1:
                dataTR.numbersimple.c = "K"; break;
            case 2:
                dataTR.numbersimple.c = "M"; break;
            case 3:
                dataTR.numbersimple.c = "G"; break;
            case 4:
                dataTR.numbersimple.c = "T"; break;
            default:
                dataTR.numbersimple.c = "?"; break;
        }

        if(dataTR.exponent.power >= 0)
            dataTR.numbersimple.base = dataTR.exponent.base * pow(10.0,remainder);
        else
            dataTR.numbersimple.base = dataTR.exponent.base * pow(10.0,remainder+2);
    }
    else
    {
        dataTR.simple = false;
    }


    return dataTR;
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
    mythread = new MyThread(serialdialog.getPort(), serialdialog.getPortSettings(), this);
    connect(mythread,SIGNAL(serialFinished(QByteArray)),this,SLOT(dataReceive(QByteArray)));
    mythread->start();

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
    mythread->msg = "*RST\r\n";
    mythread->msg.append(":SOUR:FUNC VOLT\r\n");
    mythread->msg.append(":SOUR:VOLT:MODE FIXED\r\n");
    mythread->msg.append(":SOUR:VOLT:RANG:AUTO ON\r\n");
    mythread->msg.append(":SOUR:VOLT:LEV 0\r\n");
    mythread->msg.append(":SENS:CURR:PROT 10E-5\r\n");
    mythread->msg.append(":SENS:FUNC \"CURR\"\r\n");
    mythread->msg.append(":SENS:CURR:RANG:AUTO ON\r\n");
    mythread->msg.append(":OUTP ON\r\n");
    //mythread->msg.append(":SOUR:VOLT:IMM ");
    mythread->msg.append(":SOUR:VOLT:LEV ");
    mythread->msg.append(bias);
    mythread->msg.append("\r\n");

    mythread->read = false;
    mythread->write = true;
}


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
