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
