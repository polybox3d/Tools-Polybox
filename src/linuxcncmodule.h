#ifndef LINUXCNCMODULE_H
#define LINUXCNCMODULE_H

/**
  * http://linuxcnc.org/docs/html/man/man1/hal_input.1.html
  *
  **/

#include <QString>
#include <iostream>
#include <QRegExp>

#include "JoypadWidget.h"

using namespace std;

class LinuxCNCModule
{
public:
    LinuxCNCModule( QString linuxcnc_directory, JoypadWidget* joypad);
    int checkHalFile();
    int addInputDevice( QString device_name );

private:
    JoypadWidget* _joypad;
    QString _directory;
    QString _halfile;
};

#endif // LINUXCNCMODULE_H
