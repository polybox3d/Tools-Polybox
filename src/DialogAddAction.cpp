#include "DialogAddAction.h"
#include "ui_DialogAddAction.h"

DialogAddAction::DialogAddAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddAction)
{
    ui->setupUi(this);
}

DialogAddAction::~DialogAddAction()
{
    delete ui;
}

void DialogAddAction::on_cancel_clicked()
{
    this->reject();
}

void DialogAddAction::on_add_clicked()
{
    this->accept();
}
