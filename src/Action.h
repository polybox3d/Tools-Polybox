#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <QList>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>


class Action
{
public:
    enum Type{
        Disable=0, Button=1, Axis=2
    };

    Action();
    Action( QString name, QString code, Action::Type type=(Action::Type)(Action::Button|Action::Axis) );

    int _id;
    QString _name;
    QString _code;
    Action::Type _type;
    static QList<Action*> actions;
    static int next_id;
    static void exportAction(QString filename);
    static void addAction( Action* action );
};

#endif // ACTION_H
