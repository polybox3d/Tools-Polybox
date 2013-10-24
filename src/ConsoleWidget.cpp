#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleWidget)
{
    ui->setupUi(this);
    ui->editorFrame->setHidden( true );
}

ConsoleWidget::~ConsoleWidget()
{
    delete ui;
}

void ConsoleWidget::on_editorMode_clicked()
{

}

void ConsoleWidget::on_editorMode_stateChanged(int arg1)
{
    if ( arg1 == Qt::Unchecked )
    {
        ActionButton::is_floating = false;
        ui->editorFrame->setHidden( true );
    }
    if ( arg1 == Qt::Checked )
    {
        ui->editorFrame->setHidden( false );
        ActionButton::is_floating = true;
    }
    //this->parentWidget()->parentWidget()->adjustSize();
    this->adjustSize();
}

void ConsoleWidget::on_addAction_clicked()
{
    DialogAddAction dialog(this);
    int ret =dialog.exec();
    if ( ret == QDialog::Accepted )
    {
        //Action::actions.append();
    }
}

void ConsoleWidget::on_pushButton_clicked()
{
    //ActionButton::exportCurrentAction();
}

void ConsoleWidget::on_pushButton_2_clicked()
{
    if ( _joypad != NULL )
    {
        QString filename = QFileDialog::getSaveFileName(this,
                                                        tr("File to save"),
                                                        "./current_overlay.xml");
        if ( filename != NULL )
        {
            _joypad->exportCurrentOverlay( filename );
        }

    }
}
