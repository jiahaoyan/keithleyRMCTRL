#include "biasdialog.h"
#include "ui_biasdialog.h"

BiasDialog::BiasDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BiasDialog)
{
    ui->setupUi(this);
}

BiasDialog::~BiasDialog()
{
    delete ui;
}

 double BiasDialog::getBias()
 {
     return ui->DSB_bias->value();
 }


void BiasDialog::on_PB_BiasUpdate_clicked()
{
    emit Bias_Update();
}
