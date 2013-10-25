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
    if ( _joypad != NULL )
    {
        QString filename = QFileDialog::getOpenFileName(this,tr("Select a config file"), ".", tr("Config Files (*.xml)") );
        if ( filename != NULL )
        {
         //   Action::actions.clear();
            _joypad->loadConfig( filename );
        }
    }
}

void ControleWidget::on_openJoypad_clicked()
{
    QJoystick *nJoystick = QJoystickEnumerator::enumerate("/dev/input", this);
    if(nJoystick != NULL)
    {

    }
}
