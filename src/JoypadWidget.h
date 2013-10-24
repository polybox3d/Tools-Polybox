#ifndef JOYPADWIDGET_H
#define JOYPADWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>

#include "ActionButton.h"

namespace Ui {
class JoypadWidget;
}

class JoypadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JoypadWidget(QWidget *parent = 0);
    ~JoypadWidget();

    void importOverlay(QString filename);
    void importActions( QString filename);
    void processActionsList();
    void setJoypadImage( QString image );

    void exportCurrentOverlay( QString filename );
    void exportConfig(QString name);
    QString name(){return _name;}

protected:

    void paintEvent(QPaintEvent *);

private:
    Ui::JoypadWidget *ui;

    QString _name;
    int _device_id;
    QString _overlayfile;
    QString _actiosnfile;
    void parseButton( QXmlStreamReader* xml );
    void parseAction( QXmlStreamReader* xml );
    QList<ActionButton*> _actionButton;
};

#endif // JOYPADWIDGET_H


