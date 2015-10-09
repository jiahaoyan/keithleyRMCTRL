#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    biasdialog.setModal(false);
    biasdialog.show();
}
