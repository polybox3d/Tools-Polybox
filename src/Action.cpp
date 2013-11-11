#include "Action.h"

QList<Action*> Action::actions;
int Action::next_id=0;

Action::Action()
{
    _id = Action::next_id;
    Action::next_id++;

    _name="def.";
    _code="";
    _type=(Action::Type)(Action::Axis|Action::Button);
}

Action::Action(QString name, QString code, Action::Type type) :  _name(name), _code(code), _type(type)
{
    _id = Action::next_id;
    Action::next_id++;
}


void Action::exportAction(QString filename)
{
    QFile* file = new QFile( filename );
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QXmlStreamWriter xml(file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    xml.writeStartElement("actions");

    foreach ( Action* act, Action::actions )
    {
        xml.writeStartElement("action");
        xml.writeTextElement("name", act->_name );
        xml.writeTextElement("code", act->_code );
        xml.writeTextElement("type", QString::number(act->_type) );
        xml.writeEndElement();
    }
    xml.writeEndElement();//actions
    xml.writeEndDocument();
    file->close();
}

void Action::addAction(Action *action)
{
    Action::actions.append( action );
}
