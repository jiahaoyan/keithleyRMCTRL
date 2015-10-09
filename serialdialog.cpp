#include "serialdialog.h"
#include "ui_serialdialog.h"

SerialDialog::SerialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialDialog)
{
    ui->setupUi(this);
}

SerialDialog::~SerialDialog()
{
    delete ui;
}
