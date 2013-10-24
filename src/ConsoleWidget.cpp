#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleWidget)
{
    ui->setupUi(this);
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
    }
    if ( arg1 == Qt::Checked )
    {
        ActionButton::is_floating = true;
    }
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
        _joypad->exportCurrentOverlay();
    }
}
