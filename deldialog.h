#ifndef DELDIALOG_H
#define DELDIALOG_H

#include <QDialog>

namespace Ui {
class DelDialog;
}

class DelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelDialog(QWidget *parent = nullptr);
    ~DelDialog();

signals:
    void onBtnClickedSignal(int i);

private:
    Ui::DelDialog *ui;

private slots:
    void onBtnClicked();
};

#endif // DELDIALOG_H
