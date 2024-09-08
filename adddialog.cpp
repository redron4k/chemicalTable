#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::onBtnClicked() {
    elem e;
    e.number = ui->lineEdit->text();
    e.name = ui->lineEdit_2->text();
    e.mass = ui->lineEdit_3->text();
    e.conductivity = ui->comboBox->currentText();
    emit onBtnClickedSignal(e);
    this->close();
}
