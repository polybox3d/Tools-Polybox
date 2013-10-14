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

usermod -a -G dialout $(whoami)


echoC "$BLU" "===>Download Printer Firmware..." 
reset cd
git clone https://github.com/skapin/Repetier-Firmware.git



print_bye

exit 0