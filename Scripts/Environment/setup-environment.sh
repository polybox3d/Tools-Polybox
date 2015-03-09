#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh

echoC "$BLU" "=====>Create your environment files"
resetC
cp $MY_DIR/../Configuration-Files/bashrc ~/.bashrc
cp $MY_DIR/../Configuration-Files/bash_polycom ~/.bash_polycom
source ~/.bashrc
print_check_error

#====virtu-serial
$MY_DIR/setup-virtu-serial-deamon.sh
print_check_error

#====DropBox/sharedFolders
$MY_DIR/install-samba.sh
print_check_error

#====Script Git-update
#echoC "$BLU" "=====>Setup Auto-Git-update script."
#resetC
#sudo cp $MY_DIR/git-update.sh /etc/init.d/git-update
##give right
#sudo chmod +x /etc/init.d/git-update
##update rc file for auto-start at boot
#echoC "$BLU" "===>Update RC file" ; resetC
#sudo $MY_DIR/update-rc.d git-update defaults

#====Script sys-update
echoC "$BLU" "=====>Setup Auto-sys-update script." ; resetC
sudo cp $MY_DIR/sys-update.sh /etc/init.d/sys-update
#give right
sudo chmod +x /etc/init.d/sys-update
#update rc file for auto-start at boot
echoC "$BLU" "===>Update RC file" ; resetC
sudo update-rc.d sys-update defaults


#======================= Screen+touchscreen ============================
echoC "$BLU" "=====>Configure Xorg and TouchScreen." ; resetC
CURRENT_PWD=`pwd`
cd $HOME

#if folder doesnt exist, we gonna fetch it.
if [ ! -d "$HOME/xinput_calibrator" ]; then
	git clone https://github.com/tias/xinput_calibrator.git
	print_check_error
else
	echoC "$ROSE" "xinput_calibrator already exists. Continuing."
	resetC
fi
cd xinput_calibrator
./autogen.sh
print_check_error
make
print_check_error
./src/xinput_calibrator

cd $CURRENT_PWD
sudo cp $MY_DIR/10-evdev.conf /usr/share/X11/xorg.conf.d/10-evdev.conf

## --/ BAD \--
####sudo cp $MY_DIR/xorg.conf /etc/X11/xorg.conf

#======================= DESKTOP =======================================

#theme for GTK
sudo apt-get -y install --force-yes kde-standard kdm kde-l10n-fr
print_check_error
#french
sudo apt-get -y install --force-yes kde-l10n-fr
print_check_error
#Gtk theme for kde
sudo apt-get install gtk2-engines-oxygen gtk3-engines-oxygen qtcurve kde-config-gtk-style
print_check_error


# xdotool emulate keyboard and mouse
sudo apt-get -y install qdbus-qt5 xdotool
print_check_error

sudo cp $MY_DIR/../../img/logo_vintage_halfcolor.png $HOME/wallpaper_1920x1200.png
print_check_error

js=$(mktemp)
cat > $js <<_EOF
var wallpaper = "$1";
var activity = activities()[0];
activity.currentConfigGroup = new Array("Wallpaper", "image");
activity.writeConfig("wallpaper", "$HOME/wallpaper_1920x1200.png");
activity.reloadConfig();
_EOF
qdbus org.kde.plasma-desktop /App local.PlasmaApp.loadScriptInInteractiveConsole "$js" > /dev/null
xdotool search --name "Desktop Shell Scripting Console" windowactivate --sync key --clearmodifiers ctrl+e key ctrl+w
rm -f "$js"

#==== Widgets ====


# add desktop folderview
js=$(mktemp)
cat > $js <<_EOF
var wallpaper = "";
var activity = activities()[0];
folderview = activity.addWidget ("folderview");
folderview.writeConfig("geometry", "50,50,600,400");
folderview.writeConfig("url", "Desktop://");
activity.reloadConfig();
_EOF
qdbus org.kde.plasma-desktop /App local.PlasmaApp.loadScriptInInteractiveConsole "$js" > /dev/null
xdotool search --name "Desktop Shell Scripting Console" windowactivate --sync key --clearmodifiers ctrl+e key ctrl+w
rm -f "$js"

# remove activities manager from panel 

js=$(mktemp)
cat > $js <<_EOF
panel = panelById(panelIds[0]);
panel.widgets().forEach(function(y) 
{ 
  print(y.type);
  if( y.type == 'org.kde.showActivityManager')
  {
    y.remove();
  }
}
);
_EOF
qdbus org.kde.plasma-desktop /App local.PlasmaApp.loadScriptInInteractiveConsole "$js" > /dev/null
xdotool search --name "Desktop Shell Scripting Console" windowactivate --sync key --clearmodifiers ctrl+e key ctrl+w
rm -f "$js"



#=====Create Desktop/icon =====
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
#========== Plasma ================
echoC "$BLU" "=====>Create and configure Plasma (widget,panel and theme)." ; resetC
PLASMA_DIR=/usr/share/kde4/apps/plasma-desktop/updates

sudo cp manipulatePanel.js $PLASMA_DIR
sudo cp addDock.js $PLASMA_DIR
echoC "$ROSE" "====[ Killing your plasma environement for a few moment...]=====" ; resetC
killall plasma
kbuildsycoca4 && kquitapp plasma-desktop
echoC "$ROSE" "====>Restarting plasma-desktop in 2s..." ; resetC
sleep 2

kstart plasma-desktop &


print_bye

exit 0
