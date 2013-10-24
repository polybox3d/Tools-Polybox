#include "JoypadWidget.h"
#include "ui_JoypadWidget.h"

JoypadWidget::JoypadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JoypadWidget)
{
    ui->setupUi(this);
}

JoypadWidget::~JoypadWidget()
{
    delete ui;
}

void JoypadWidget::exportCurrentOverlay()
{

    QFile* file = new QFile("overlay_cc.xml");
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical( this,
                              "Save to XML file",
                              "Couldn't write to ",
                              QMessageBox::Ok);
        return;
    }
    QXmlStreamWriter xml(file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    xml.writeStartElement("joypad-overlay");
    xml.writeTextElement("name", _name);
    xml.writeTextElement("id", QString::number(_device_id) );
    foreach ( ActionButton* act, _actionButton )
    {
        xml.writeStartElement("button");
        xml.writeTextElement("name",  act->name());
        xml.writeTextElement("id", QString::number(act->id()) );
        xml.writeTextElement("x", QString::number(act->pos().x()) );
        xml.writeTextElement("y", QString::number(act->pos().y()) );
        xml.writeEndElement();//color
    }
    xml.writeEndElement();//overlay-joypad
    xml.writeEndDocument();
    file->close();





}

void JoypadWidget::setJoypadImage(QString image)
{
    this->setObjectName("JoypadWidget");
    this->setStyleSheet("#JoypadWidget{background-image: url("+image+");background-repeat:no-repeat;}");
}


void JoypadWidget::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }

void JoypadWidget::importActions(QString filename)
{
    QFile* file = new QFile(filename);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError())
    {
        QMap<QString, QString> config;
        // Let's check that we're really getting a config.
        if( xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "actions") {
            return;
        }

        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "actions")) {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() == "action")
                {
                    parseAction( &xml );
                }
                xml.readNext();
            }
            xml.readNext();
        }
        xml.readNext();
    }
}
void JoypadWidget::processActionsList()
{
    QStringList list;
    list.reserve( Action::actions.size() );
    foreach( Action* act, Action::actions )
    {
        list.append( act->_name );
    }

    foreach(ActionButton* ab, _actionButton)
    {
        ab->setActionList( list );
    }
}

void JoypadWidget::parseAction(QXmlStreamReader *xml)
{
    Action* action ;
    while(!(xml->tokenType() == QXmlStreamReader::EndElement && xml->name() == "action"))
    {
        if(xml->tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml->name() == "name")
            {
                xml->readNext();
                action = new Action();
                action->_name = xml->text().toString();
            }
            if(xml->name() == "id")
            {
                xml->readNext();
                action->_id = xml->text().toInt();
            }
            if(xml->name() == "code")
            {
                xml->readNext();
                action->_code = xml->text().toString();
            }
            if(xml->name() == "type")
            {
                xml->readNext();
                action->_type = (Action::Type)(xml->text().toInt());
            }
        }
        xml->readNext();
    }
    Action::actions.append( action );
}

void JoypadWidget::importOverlay(QString filename)
{
    QFile* file = new QFile(filename);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError())
    {
        QMap<QString, QString> config;
        // Let's check that we're really getting a config.
        if( xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "joypad-overlay") {
            return;
        }

        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "joypad-overlay")) {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() == "name")
                {
                    xml.readNext();
                    _name = xml.text().toString();
                }
                if(xml.name() == "device-id")
                {
                    xml.readNext();
                    xml.text().toInt() ;
                }
                if(xml.name() == "button") {
                    parseButton( &xml );
                }
                xml.readNext();
            }
            xml.readNext();
        }
        xml.readNext();
    }
}


void JoypadWidget::parseButton(QXmlStreamReader *xml)
{
    ActionButton *current_button;
    QString name;
    int x,y;
    while(!(xml->tokenType() == QXmlStreamReader::EndElement && xml->name() == "button"))
    {
        if(xml->tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml->name() == "name")
            {
                xml->readNext();
                name = xml->text().toString();
            }
            if(xml->name() == "id")
            {
                xml->readNext();
                current_button = new ActionButton( name, xml->text().toInt(), this);
            }
            if(xml->name() == "img")
            {
                xml->readNext();
                current_button->setImage(xml->text().toString());
            }
            if(xml->name() == "x")
            {
                xml->readNext();
                x = xml->text().toInt();
            }
            if(xml->name() == "y")
            {
                xml->readNext();
                y = xml->text().toInt();
                current_button->setGeometry(x, y, this->width(), this->height() );
            }
            if(xml->name() == "list-position")
            {
                xml->readNext();
                current_button->setListPosition((ActionButton::Position)xml->text().toInt() );
            }
        }
        xml->readNext();
    }
    _actionButton.append( current_button );
    current_button->adjustSize();
}
