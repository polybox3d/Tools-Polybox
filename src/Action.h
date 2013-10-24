#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <QList>

class Action
{
public:
    enum Type{
        Disable=0, Button=1, Axis=2
    };

    Action();
    Action(int id, QString name, QString code, Action::Type type=(Action::Type)(Action::Button|Action::Axis) );

    int _id;
    QString _name;
    QString _code;
    Action::Type _type;
    static QList<Action*> actions;
    static void exportCurrentAction();
};

#endif // ACTION_H
