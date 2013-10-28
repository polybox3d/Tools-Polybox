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

void ControleWidget::on_applyCNC_clicked()
{
    if ( _joypad != NULL )
    {
        QString filename = QFileDialog::getExistingDirectory(this, tr("Your Mill directory"),
                                                             "/home/poly/linuxcnc/configs/",
                                                             QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if ( filename != NULL )
        {
            LinuxCNCModule cnc(filename, _joypad);
            if ( cnc.checkHalFile() == 0 ) // 0 = no error
            {
                if ( cnc.addInputDevice( _joypad->name() ) == 0 )
                {
                    QMessageBox::information( this,
                                          "Done ! ",
                                        "Your joypad "+_joypad->name()+" is added in LinuxCNC !",
                                          QMessageBox::Ok);
                }
                else
                {
                    QMessageBox::critical( this,
                                          "Error While opening ",
                                          "Couldn't open the file",
                                          QMessageBox::Ok);
                }
            }
            else {
                QMessageBox::critical( this,
                                      "Error While opening or reading",
                                      "Couldn't open the given directory or soemthing went wrong. Like no HALFILE specified",
                                      QMessageBox::Ok);
            }
        }
    }
}
