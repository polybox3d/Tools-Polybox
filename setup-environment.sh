#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh


echoC "$BLU" "=====>Create your environment files"
resetC
cp .bashrc ~/
cp .bash_polycom ~/
source ~/.bashrc
print_check_ok

sudo cp ./img/logo_vintage_halfcolor_trunc.png /usr/share/wallpapers/Ariya/contents/images/1920x1200.png

#====virtu-serial
./setup-virtu-serial-deamon.sh
./setup-polyplexer-deamon.sh

#===Create Desktop/icon
echoC "$BLU" "=====>Create and setup Desktop Icon ."
#cp ./Desktop/* ~/Dekstop/
#cp ./Desktop/* ~/Bureau/
xdg-desktop-icon install dolphin.dekstop
xdg-desktop-icon install konsole.dekstop
xdg-desktop-icon install firefox.dekstop
xdg-desktop-icon install polybox-cnc.dekstop
resetC

#====DropBox/sharedFolders
./install-samba

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

#====Script Git-update
echoC "$BLU" "=====>Setup Auto-Git-update script."
resetC
sudo cp git-update.sh /etc/init.d/git-update
#give right
sudo chmod +x /etc/init.d/git-update
#update rc file for auto-start at boot
echoC "$BLU" "===>Update RC file"
sudo update-rc.d git-update defaults


#==== Screen+touchscreen
echoC "$BLU" "=====>Configure Xorg and TouchScreen."
resetC
sudo cp 10-evdev.conf /usr/share/X11/xorg.conf.d/10-evdev.conf
sudo cp xorg.conf /etc/X11/xorg.conf



print_bye

exit 0