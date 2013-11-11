#ifndef JOYPADWIDGET_H
#define JOYPADWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <iostream>

#include "qjoystick.h"
#include "qjoystickenumerator.h"

using namespace std;

#include "ActionButton.h"

namespace Ui {
class JoypadWidget;
}

class JoypadWidget : public QWidget
{
    Q_OBJECT

public:

    QJoystick* joystick;
    explicit JoypadWidget(QWidget *parent = 0);
    ~JoypadWidget();

    void importOverlay(QString filename);
    void importActions( QString filename);
    void processActionsList();
    void setJoypadImage( QString image );

    void exportCurrentOverlay( QString filename );

    void exportConfig(QString filename);
    void loadConfig( QString filename );

    void showButtonId();
    void showActionList();
    QString name(){return _name;}
    void resetActionButton();
    void setColorButton( int id );

public slots:

    void updateAxis(int n,short v);
    void updateButton(int n, bool v);


protected:

    void paintEvent(QPaintEvent *);

private:
    Ui::JoypadWidget *ui;

    QString _name;
    QString _image;
    QString _device_id;
    QString _overlayfile;
    QString _actiosnfile;
    void parseButton( QXmlStreamReader* xml );
    void parseAction( QXmlStreamReader* xml );
    QList<ActionButton*> _actionButton;
};

#endif // JOYPADWIDGET_H


