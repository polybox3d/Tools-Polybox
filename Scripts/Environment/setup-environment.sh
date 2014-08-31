#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh


echoC "$BLU" "=====>Create your environment files"
resetC
cp $MY_DIR/../Configuration-Files/bashrc ~/.bashrc
cp $MY_DIR/../Configuration-Files/bash_polycom ~/.bash_polycom
source ~/.bashrc
print_check_ok

sudo cp $MY_DIR/../../img/logo_vintage_halfcolor_trunc.png /usr/share/wallpapers/Ariya/contents/images/1920x1200.png

#====virtu-serial
./setup-virtu-serial-deamon.sh

#====DropBox/sharedFolders
./install-samba.sh


#====Script Git-update
echoC "$BLU" "=====>Setup Auto-Git-update script."
resetC
sudo cp git-update.sh /etc/init.d/git-update
#give right
sudo chmod +x /etc/init.d/git-update
#update rc file for auto-start at boot
echoC "$BLU" "===>Update RC file"
sudo update-rc.d git-update defaults

#====Script sys-update
echoC "$BLU" "=====>Setup Auto-sys-update script."
resetC
sudo cp sys-update.sh /etc/init.d/sys-update
#give right
sudo chmod +x /etc/init.d/sys-update
#update rc file for auto-start at boot
echoC "$BLU" "===>Update RC file"
sudo update-rc.d sys-update defaults


#==== Screen+touchscreen
echoC "$BLU" "=====>Configure Xorg and TouchScreen."
resetC
sudo cp 10-evdev.conf /usr/share/X11/xorg.conf.d/10-evdev.conf
sudo cp xorg.conf /etc/X11/xorg.conf




#===Create Desktop/icon
echoC "$BLU" "=====>Create and setup Desktop Icon ."
resetC
#cp ./Desktop/* ~/Dekstop/
#cp ./Desktop/* ~/Bureau/
cd ../../Desktop
xdg-desktop-icon install --novendor dolphin.desktop
xdg-desktop-icon install --novendor konsole.desktop
xdg-desktop-icon install --novendor firefox.desktop
xdg-desktop-icon install --novendor polybox-cnc.desktop
xdg-desktop-icon install --novendor plbx-dropbox.desktop

#change default browser
xdg-settings set default-web-browser firefox.desktop

#add menu entries for KMenu
./setup-menu.sh

cd ..
#====Plasma
echoC "$BLU" "=====>Create and configure Plasma (widget,panel and theme)."
resetC
PLASMA_DIR=/usr/share/kde4/apps/plasma-desktop/updates

sudo cp manipulatePanel.js $PLASMA_DIR
sudo cp addDock.js $PLASMA_DIR
echoC "$ROSE" "====[ Killing your plasma environement for a few moment...]====="
killall plasma
kbuildsycoca4 && kquitapp plasma-desktop
echoC "$ROSE" "====>Restarting plasma-desktop in 2s..."
resetC
sleep 2

kstart plasma-desktop &


print_bye

exit 0
