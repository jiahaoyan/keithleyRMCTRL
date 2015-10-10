#include "serialdialog.h"
#include "ui_serialdialog.h"

SerialDialog::SerialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialDialog)
{
    ui->setupUi(this);
    ui->PB_close->setDisabled(true);

}

SerialDialog::~SerialDialog()
{
    delete ui;
}

QString SerialDialog::getPort()
{
    return ui->CB_port->currentText();
}

struct PortSettings SerialDialog::getPortSettings()
{
    portsettings.BaudRate = (BaudRateType) ui->CB_buadRate->currentIndex();
    portsettings.DataBits = (DataBitsType) ui->CB_dataBits->currentIndex();
    portsettings.Parity = (ParityType) ui->CB_parity->currentIndex();
    portsettings.StopBits = (StopBitsType) ui->CB_stopBits->currentIndex();
    portsettings.FlowControl = (FlowType) ui->CB_flowType->currentIndex();
    portsettings.Timeout_Millisec = (long) ui->SB_timeOut->value();

    return portsettings;
}

void SerialDialog::on_PB_connect_clicked()
{
    ui->PB_connect->setDisabled(true);
    ui->PB_close->setDisabled(false);

    ui->CB_port->setDisabled(true);
    ui->CB_buadRate->setDisabled(true);
    ui->CB_dataBits->setDisabled(true);
    ui->CB_parity->setDisabled(true);
    ui->CB_stopBits->setDisabled(true);
    ui->CB_flowType->setDisabled(true);
    ui->SB_timeOut->setDisabled(true);

    emit Serial_connect();
}

void SerialDialog::on_PB_close_clicked()
{
    ui->PB_close->setDisabled(true);
    ui->PB_connect->setDisabled(false);

    ui->CB_port->setDisabled(false);
    ui->CB_buadRate->setDisabled(false);
    ui->CB_dataBits->setDisabled(false);
    ui->CB_parity->setDisabled(false);
    ui->CB_stopBits->setDisabled(false);
    ui->CB_flowType->setDisabled(false);
    ui->SB_timeOut->setDisabled(false);

    emit Serial_close();
}
