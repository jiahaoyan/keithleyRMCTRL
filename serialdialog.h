#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>
#include "include/qextserialbase.h"
#include "include/win_qextserialport.h"

namespace Ui {
class SerialDialog;
}

class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialDialog(QWidget *parent = 0);
    ~SerialDialog();

    QString getPort();
    struct PortSettings getPortSettings();

signals:
    void Serial_connect();
    void Serial_close();

private slots:

    void on_PB_connect_clicked();

    void on_PB_close_clicked();

private:
    Ui::SerialDialog *ui;
    struct PortSettings portsettings;
};

#endif // SERIALDIALOG_H
