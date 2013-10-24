#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QStringList>
#include <QComboBox>
#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include <QGridLayout>
#include <iostream>

#include "Action.h"

using namespace std;

class ActionButton : public QComboBox
{
    Q_OBJECT
public:
    enum Position
    {
        Top, Bottom, Left, Right
    };

    enum HideFlag
    {
        Never=0, OnFocus=1, OnHover=2
    };

    explicit ActionButton(QWidget *parent = 0);
    ActionButton(QString name, int id, QWidget *parent);

    void setImage( QString image_nochecked, QString image_checked="" );
    void setActionList( const QStringList &value);
    void setListPosition( ActionButton::Position position );
    void setAutoHide( ActionButton::HideFlag );

    static bool is_floating;
    QString name() { return _name; }
    int id() { return _id; }

signals:

public slots:

protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);

private:
   //  QComboBox* _list;
     QString _name;
     int _id;
     QPoint _offset;

};

#endif // ACTIONBUTTON_H
