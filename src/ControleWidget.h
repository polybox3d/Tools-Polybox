#ifndef CONTROLEWIDGET_H
#define CONTROLEWIDGET_H

#include <QWidget>
#include <QFileDialog>

#include "JoypadWidget.h"
#include "qjoystick.h"
#include "qjoystickenumerator.h"

namespace Ui {
class ControleWidget;
}

class ControleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControleWidget(QWidget *parent = 0);
    void addJoypadOverlay( JoypadWidget* joy) { _joypad = joy;}
    ~ControleWidget();

private slots:
    void on_saveConf_clicked();

    void on_laodConf_clicked();

    void on_openJoypad_clicked();

private:
    Ui::ControleWidget *ui;
    JoypadWidget* _joypad;
};

#endif // CONTROLEWIDGET_H
