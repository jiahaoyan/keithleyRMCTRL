#include "modeldialog.h"
#include "ui_modeldialog.h"

ModelDialog::ModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelDialog)
{
    ui->setupUi(this);
}

ModelDialog::~ModelDialog()
{
    delete ui;
}
