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

void ControleWidget::on_saveConf_clicked()
{
    if ( _joypad != NULL )
    {
        QString filename = QFileDialog::getSaveFileName(this,
                                                        tr("File to save"),
                                                        "./"+_joypad->name()+"_conf.xml");
        if ( filename != NULL )
        {
            _joypad->exportConfig( filename );
        }
    }
}

void ControleWidget::on_laodConf_clicked()
{
    //_joypad->
}
