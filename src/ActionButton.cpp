#include "ActionButton.h"


bool ActionButton::is_floating=false;

ActionButton::ActionButton(QWidget *parent) :
    QComboBox(parent)
{
    this->adjustSize();
}

ActionButton::ActionButton(QString name, int id, QWidget *parent) :
    QComboBox(parent)
{
    _name = name;
    _id = id;
    this->adjustSize();
}
void ActionButton::setCurrentActionById(int id)
{
    QString txt;
    foreach( Action* act, Action::actions )
    {
        if ( act->_id == id )
        {
            txt = act->_name;
        }
    }
    int ret = this->findText( txt );
    if ( ret != -1 )
    {
        this->setCurrentIndex( ret );
    }
    else
    {

    }
}

void ActionButton::showButtonName()
{
    this->clear();
    this->addItem( _name );
    this->adjustSize();
}

void ActionButton::showActionList()
{
    this->clear();
    this->setList( _savedlist );
    this->adjustSize();
}


Action* ActionButton::currentAction()
{

    foreach( Action* act, Action::actions )
    {
        if ( act->_id == this->itemData( this->currentIndex() ).toInt() )
        {
            return act;
        }
    }

    return NULL;
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

void ActionButton::setList( QList<Action*> list )
{
    _savedlist = list;
    foreach( Action* act, list )
    {
        this->addItem( act->_name, act->_id);
    }
    this->adjustSize();
}

