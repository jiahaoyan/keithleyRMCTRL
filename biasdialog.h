#ifndef BIASDIALOG_H
#define BIASDIALOG_H

#include <QDialog>

namespace Ui {
class BiasDialog;
}

class BiasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BiasDialog(QWidget *parent = 0);
    ~BiasDialog();

    double getBias();

signals:
    void Bias_Update();

private slots:
    void on_PB_BiasUpdate_clicked();

private:
    Ui::BiasDialog *ui;
};

#endif // BIASDIALOG_H
