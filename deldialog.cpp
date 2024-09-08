#include "deldialog.h"
#include "ui_deldialog.h"

DelDialog::DelDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DelDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
}

DelDialog::~DelDialog()
{
    delete ui;
}

void DelDialog::onBtnClicked() {
    int i = ui->lineEdit->text().toInt();
    emit onBtnClickedSignal(i);
    this->close();
}
