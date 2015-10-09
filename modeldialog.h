#ifndef MODELDIALOG_H
#define MODELDIALOG_H

#include <QDialog>

namespace Ui {
class ModelDialog;
}

class ModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelDialog(QWidget *parent = 0);
    ~ModelDialog();

private:
    Ui::ModelDialog *ui;
};

#endif // MODELDIALOG_H
