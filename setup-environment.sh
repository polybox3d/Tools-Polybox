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

sudo cp ./img/logo_vintage_halfcolor.png /usr/share/wallpapers/Ariya/contents/images/1920x1200.png

#====Plasma
echoC "$BLU" "=====>Create and configure Plasma (widget,panel and theme)."
resetC
PLASMA_DIR=/usr/share/kde4/apps/plasma-desktop/updates

sudo cp manipulatePanel.js $PLASMA_DIR
sudo cp addDock.js $PLASMA_DIR
echoC "$ROSE" "====[ Killing your plasma environement for a few moment...]====="
killall plasma
echoC "$ROSE" "====>Restarting plasma-desktop in 2s..."
resetC
sleep 2

plasma-desktop

print_bye

exit 0