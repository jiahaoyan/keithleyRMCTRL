#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mythread.h"

#include "serialdialog.h"
#include "aboutdialog.h"
#include "modeldialog.h"
#include "biasdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SerialDialog serialdialog;
    AboutDialog aboutdialog;
    ModelDialog modeldialog;
    BiasDialog biasdialog;

public slots:

    void SerialDialog_PB_connect_clicked();
    void SerialDialog_PB_close_clicked();
    void BiasDialog_PB_BiasUpdate_clicked();

    void dataReceive(QByteArray data);

private slots:


    void on_actionAbout_triggered();

    void on_actionSerial_triggered();

    void on_actionExit_triggered();

    void on_actionModel_triggered();

    void on_actionBias_Set_triggered();

private:
    Ui::MainWindow *ui;
    MyThread *mythread;
};

#endif // MAINWINDOW_H
