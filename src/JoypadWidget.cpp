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
void JoypadWidget::updateAxis(int n,short v)
{
    ui->buttonId->setText( QString::number(n));
    ui->value->setText( QString::number(v));
    setColorButton( n );
}

void JoypadWidget::updateButton(int n, bool v)
{
    if ( v )
    {
        ui->value->setText( "Pressed" );
    }
    else
    {
        ui->value->setText( "Released" );
    }
    ui->buttonId->setText( QString::number(n));
    setColorButton( n );
}

void JoypadWidget::setColorButton( int id )
{
    foreach(ActionButton* ab, _actionButton)
    {
        if ( ab->id() == id )
        {
            ab->setStyleSheet("background-color:#66A766;");
            //break;
        }
        else
        {
            ab->setStyleSheet("background-color:#FFFFFF;");
        }
    }
}

void JoypadWidget::loadConfig( QString filename )
{
    QFile* file = new QFile(filename);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    _actiosnfile = filename;
    int button;
    int action;
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError())
    {
        QMap<QString, QString> config;
        // Let's check that we're really getting a config.
        if( xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "config") {
            return;
        }

        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "config")) {
            if(xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if(xml.name() == "overlay-file")
                {
                    xml.readNext();
                    this->resetActionButton();
                    this->importOverlay( xml.text().toString() );
                }
                if(xml.name() == "action-file")
                {
                    xml.readNext();
                    Action::actions.clear();
                    Action::next_id=0;
                    this->importActions( xml.text().toString() ) ;
                    this->processActionsList();
                }
                if(xml.name() == "assoc")
                {
                    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "assoc"))
                    {
                        if(xml.tokenType() == QXmlStreamReader::StartElement)
                        {
                            if(xml.name() == "button-id")
                            {
                                xml.readNext();
                                button = xml.text().toString().toInt();
                            }
                            if(xml.name() == "action-id")
                            {
                                xml.readNext();
                                action = xml.text().toString().toInt();
                            }
                        }
                        xml.readNext();
                    }
                    foreach(ActionButton* ab, _actionButton)
                    {
                        if ( ab->id() == button )
                        {
                            ab->setCurrentActionById( action );
                            //break;
                        }
                    }

                }
                xml.readNext();
            }
            xml.readNext();
        }
        xml.readNext();
    }
}

void JoypadWidget::resetActionButton()
{
    foreach(ActionButton* ab, _actionButton)
    {
        delete ab;
    }
    _actionButton.clear();
}


void JoypadWidget::exportConfig( QString filename )
{
    QFile* file = new QFile( filename );
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

    xml.writeStartElement("config");
    xml.writeTextElement("overlay-file", _overlayfile );
    xml.writeTextElement("action-file", _actiosnfile );
    foreach ( ActionButton* act, _actionButton )
    {
        xml.writeStartElement("assoc");
        xml.writeTextElement("button-id", QString::number(act->id()) );
        xml.writeTextElement("action-id", QString::number(act->currentAction()->_id) );
        xml.writeEndElement();//color
    }
    xml.writeEndElement();//overlay-joypad
    xml.writeEndDocument();
    file->close();

}

void JoypadWidget::exportCurrentOverlay( QString filename)
{

    QFile* file = new QFile( filename );
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
    xml.writeTextElement("id", _device_id );
    xml.writeTextElement("img", _image);
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
    this->_image = image;
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
    _actiosnfile = filename;
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
            }
            xml.readNext();
        }
        xml.readNext();
    }
}
void JoypadWidget::showButtonId()
{
    foreach(ActionButton* ab, _actionButton)
    {
        ab->showButtonName();
    }
}
void JoypadWidget::showActionList()
{
    this->processActionsList();
}

void JoypadWidget::processActionsList()
{
    foreach(ActionButton* ab, _actionButton)
    {
        //ab->setActionList( list );
        ab->clear();
        ab->setList( Action::actions );
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
            /*if(xml->name() == "id")
            {
                xml->readNext();
                action->_id = xml->text().toString().toInt();
            }*/
            if(xml->name() == "code")
            {
                xml->readNext();
                action->_code = xml->text().toString();
            }
            if(xml->name() == "type")
            {
                xml->readNext();
                action->_type = (Action::Type)(xml->text().toString().toInt());
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
        cout<<"Can't open"<<endl;
        return;
    }
    _overlayfile = filename;
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
                    _device_id = xml.text().toString() ;
                }
                if(xml.name() == "img")
                {
                    xml.readNext();
                    this->setJoypadImage( xml.text().toString() ) ;
                }
                if(xml.name() == "button") {
                    parseButton( &xml );
                }
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
                current_button = new ActionButton( name, xml->text().toString().toInt(), this);
            }
            if(xml->name() == "x")
            {
                xml->readNext();
                x = xml->text().toString().toInt();
            }
            if(xml->name() == "y")
            {
                xml->readNext();
                y = xml->text().toString().toInt();
                current_button->setGeometry(x, y, this->width(), this->height() );
            }
        }
        xml->readNext();
    }
    _actionButton.append( current_button );
    current_button->show();
    current_button->adjustSize();
}
