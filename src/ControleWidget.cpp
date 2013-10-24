#include "ControleWidget.h"
#include "ui_ControleWidget.h"

ControleWidget::ControleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControleWidget)
{
    ui->setupUi(this);
}

ControleWidget::~ControleWidget()
{
    delete ui;
}
