#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "mainwindow.h"

struct elem;

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

signals:
    void onBtnClickedSignal(elem e);

private:
    Ui::AddDialog *ui;
private slots:
    void onBtnClicked();
};

#endif // ADDDIALOG_H
