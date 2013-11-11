#include "linuxcncmodule.h"

LinuxCNCModule::LinuxCNCModule(QString linuxcnc_directory, JoypadWidget *joypad) : _directory(linuxcnc_directory), _joypad(joypad)
{
}

int LinuxCNCModule::addInputDevice(QString device_name)
{
    QFile file( _directory+"/"+_halfile);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
    {
        cerr<<"Error opening file"<< _directory.toStdString()<<"/"<<_halfile.toStdString()<<endl;
        return 1;
    }
    file.write("\n#Auto-Add by JoypadOverlay software. Remote joypad control\n");
    file.write((QString("loadusr -W hal_input -KRAL \"")+device_name+"\"\n").toStdString().c_str());
    return 0;
}

int LinuxCNCModule::checkHalFile()
{
    QFile file( _directory+"/"+_directory.split('/').last()+".ini");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cerr<<"Error opening file"<< _directory.toStdString()+"/"+_directory.split('/').last().toStdString()+".ini"<<endl;
        return 1;
    }
    QRegExp find_halfile("^HALFILE[\\s]*");
    QRegExp find_halui("^HALUI[\\s]*");
    QString hal_file;
    bool halui_find = false;
    bool halfile_find = false;
    while (!file.atEnd() && !(halfile_find && halui_find))
    {
        QByteArray line = file.readLine();
        if ( QString(line).contains( find_halfile ))
        {
            halfile_find = true;
            _halfile = QString(line).split('=').last().trimmed();
        }
        if ( QString(line).contains( find_halui ))
        {
            halui_find = true;
        }

    }
    if ( halfile_find == false )
    {
        cerr<<"Error, I can't find HAL file..."<<endl;
        return 2;
    }
    if ( halui_find == false )
    {
        cerr<<"Error, I can't find HALUI mode on..."<<endl;
        return 4;
    }
    return 0;
}

