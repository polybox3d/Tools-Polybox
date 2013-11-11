#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleWidget)
{
    ui->setupUi(this);
    ui->editorFrame->setHidden( true );
    _edited = false;
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
        _joypad->showActionList();
        ui->editorFrame->setHidden( true );
        if ( _edited )
        {
            QMessageBox::critical( this,
                                  "Save modification ?",
                                  "You have edited some information, you should save your current action file. If you export the config file without saving action or overlay file, the file will be corrupted",
                                  QMessageBox::Ok);
        }
    }
    if ( arg1 == Qt::Checked )
    {
        ui->editorFrame->setHidden( false );
        _joypad->showButtonId();
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
        _edited = true;
        //_joypad->processActionsList();
    }

}

void ConsoleWidget::on_pushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("File to save"),
                                                    "./current_overlay.xml");
    if ( filename != NULL && !filename.isEmpty())
    {
        Action::exportAction( filename );
    }

}

void ConsoleWidget::on_pushButton_2_clicked()
{
    if ( _joypad != NULL )
    {
        QString filename = QFileDialog::getSaveFileName(this,
                                                        tr("File to save"),
                                                        "./current_overlay.xml");
        if ( filename != NULL && !filename.isEmpty() )
        {
            _joypad->exportCurrentOverlay( filename );
        }

    }
}
