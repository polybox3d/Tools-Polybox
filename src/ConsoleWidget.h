#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QFileDialog>

#include "ActionButton.h"
#include "Action.h"
#include "DialogAddAction.h"
#include "JoypadWidget.h"

namespace Ui {
class ConsoleWidget;
}

class ConsoleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleWidget(QWidget *parent = 0);
    void addJoypadOverlay( JoypadWidget* joy) { _joypad = joy;}
    ~ConsoleWidget();

private slots:
    void on_editorMode_clicked();

    void on_editorMode_stateChanged(int arg1);

    void on_addAction_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ConsoleWidget *ui;
    JoypadWidget* _joypad;
};

#endif // CONSOLEWIDGET_H


