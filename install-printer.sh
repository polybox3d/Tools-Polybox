#!/bin/bash
#########################################
#
# Printer script. 
# Install printer software and firmware
#
##########################################
MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

PRINTRUNDIR="$HOME/Printrun"
SKEINFORGEDIR="$PRINTRUNDIR/skeinforge"

echoC "$BLU" "*******Starting Printer installation Script.*******"
echo "This script will install prinetr software."


echoC "$BLU" "===>Get and configure Mono..." 
resetC
sudo apt-get -y install mono-complete
print_check_error

echoC "$BLU" "===>Download Printer Software..." 
resetC

cd ~
wget -O repetierHostLinux.tgz 'http://www.repetier.com/?wpdmact=process&did=NDAuaG90bGluaw=='
tar -xzf repetierHostLinux.tgz
cd RepetierHost
sh configureFirst.sh

sudo usermod -a -G dialout $(whoami)


echoC "$BLU" "===>Download Printer Softwer (printrun)..." 
resetC


cd $HOME
echo "Removing existing Printrun directory..."
rm -rf $PRINTRUNDIR
echo "Cloning Printrun..."
git clone https://github.com/kliment/Printrun.git
echo "Grabbing skeinforge..."
wget -P /tmp http://fabmetheus.crsndoo.com/files/41_reprap_python_beanshell.zip
echo "Unzipping skeinforge into Printrun directory..."
unzip -d $SKEINFORGEDIR /tmp/41_reprap_python_beanshell.zip
echo "Symlinking skeinforge inside Printrun directory..."
ln -s $SKEINFORGEDIR/* $PRINTRUNDIR/
echo "Cleaning up temporary installation files..."
rm -rf /tmp/41_reprap_python_beanshell.zip



echoC "$BLU" "===>Download Printer Firmware..." 
resetC
cd ~
git clone https://github.com/skapin/Repetier-Firmware.git



print_bye

exit 0