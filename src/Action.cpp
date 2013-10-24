#include "Action.h"

QList<Action*> Action::actions;

Action::Action()
{
    _id=-1;
    _name="def.";
    _code="";
    _type=(Action::Type)(Action::Axis|Action::Button);
}

Action::Action(int id, QString name, QString code, Action::Type type) : _id(id), _name(name), _code(code), _type(type)
{
}


void Action::exportCurrentAction()
{


}
