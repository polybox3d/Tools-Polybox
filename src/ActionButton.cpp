#include "ActionButton.h"


bool ActionButton::is_floating=false;

ActionButton::ActionButton(QWidget *parent) :
    QComboBox(parent)
{
    //this->setGeometry( this->x(), this->y(), 60, 60);
    //_button = new QPushButton("Button", this);
    //_list = new QComboBox( this );

    //_button->setCheckable( true );
    //_button->setFlat( true );
    this->adjustSize();
}

ActionButton::ActionButton(QString name, int id, QWidget *parent) :
    QComboBox(parent)
{
    //this->setGeometry( this->x(), this->y(), 400, 60);
 //   this->setGeometry( this->x(), this->y(), 60, 60);
   // _list = new QComboBox( this );

    _name = name;
    _id = id;
    this->adjustSize();

}


void ActionButton::mousePressEvent(QMouseEvent *event)
{
    if ( ActionButton::is_floating )
    {
        _offset = event->pos();
    }
    else
    {
        QComboBox::mousePressEvent(event);
    }
}
void ActionButton::mouseMoveEvent(QMouseEvent *event)
{
    if ( ActionButton::is_floating )
    {
        if(event->buttons() & Qt::LeftButton)
        {
            this->move(mapToParent(event->pos() - _offset));
        }
    }

    QComboBox::mouseMoveEvent(event);
}


void ActionButton::setImage( QString image_nochecked, QString image_checked )
{
}

void ActionButton::setActionList( const QStringList &value)
{
    this->addItems( value );
    this->adjustSize();
}
void ActionButton::setListPosition(ActionButton::Position position)
{

    this->adjustSize();

}
void ActionButton::setAutoHide( ActionButton::HideFlag )
{

}
