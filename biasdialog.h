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

private:
    Ui::BiasDialog *ui;
};

#endif // BIASDIALOG_H
