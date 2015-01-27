#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh
dirname $0
echoC "$BLU" "=====>Create your environment files"
resetC
cp $MY_DIR/../Configuration-Files/bashrc ~/.bashrc
cp $MY_DIR/../Configuration-Files/bash_polycom ~/.bash_polycom
source ~/.bashrc
print_check_error

sudo cp $MY_DIR/../../img/logo_vintage_halfcolor.png /usr/share/wallpapers/Ariya/contents/images/1920x1200.png

#====virtu-serial
$MY_DIR/setup-virtu-serial-deamon.sh

#====DropBox/sharedFolders
$MY_DIR/install-samba.sh


#====Script Git-update
echoC "$BLU" "=====>Setup Auto-Git-update script."
resetC
sudo cp $MY_DIR/git-update.sh /etc/init.d/git-update
#give right
sudo chmod +x /etc/init.d/git-update
#update rc file for auto-start at boot
echoC "$BLU" "===>Update RC file"
sudo $MY_DIR/update-rc.d git-update defaults

#====Script sys-update
echoC "$BLU" "=====>Setup Auto-sys-update script."
resetC
sudo cp $MY_DIR/sys-update.sh /etc/init.d/sys-update
#give right
sudo chmod +x /etc/init.d/sys-update
#update rc file for auto-start at boot
echoC "$BLU" "===>Update RC file"
sudo update-rc.d sys-update defaults


#==== Screen+touchscreen
echoC "$BLU" "=====>Configure Xorg and TouchScreen."
resetC
sudo cp $MY_DIR/10-evdev.conf /usr/share/X11/xorg.conf.d/10-evdev.conf
sudo cp $MY_DIR/xorg.conf /etc/X11/xorg.conf




#===Create Desktop/icon
echoC "$BLU" "=====>Create and setup Desktop Icon ."
resetC
#cp ./Desktop/* ~/Dekstop/
#cp ./Desktop/* ~/Bureau/
cd $MY_DIR/../../Desktop
xdg-desktop-icon install --novendor dolphin.desktop
xdg-desktop-icon install --novendor konsole.desktop
xdg-desktop-icon install --novendor firefox.desktop
xdg-desktop-icon install --novendor polybox.desktop
xdg-desktop-icon install --novendor polybox-cnc.desktop
xdg-desktop-icon install --novendor plbx-dropbox.desktop


#change default browser
xdg-settings set default-web-browser firefox.desktop

#add menu entries for KMenu
./setup-menu.sh

cd ../Scripts/$MY_DIR
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
