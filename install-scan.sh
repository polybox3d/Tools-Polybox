#!/bin/bash
#########################################
#
# Scanner install script. 
# Install, compile and configure scanning software
#
##########################################
SCAN_LASER_DIR="FabScan100"

MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

echoC "$BLU" "=====Scanner 3D"
resetC

sudo add-apt-repository -y ppa:v-launchpad-jochen-sprickerhof-de/pcl
sudo apt-get -y update
print_check_error
sudo apt-get -y install libpcl-all uvccapture
print_check_error
sudo adduser "$USER" dialout


#======FAB SCAN100======
#echoC "$BLU" "=====>Fetch Scanning software"
#resetC
#cd ~/

#if [ -d "$SCAN_LASER_DIR" ]; then
#    rm -Rf "$SCAN_LASER_DIR"
#fi
#git clone git://github.com/skapin/FabScan100.git "$SCAN_LASER_DIR"
#print_check_error
#cd "$SCAN_LASER_DIR"
#print_check_error
#======Compile FabScan======
#echoC "$BLU" "=====>Compile"
#resetC

#cd qtTest/
#/usr/lib/i386-linux-gnu/qt5/bin/qmake
#print_check_error
#make
#print_check_error

#print_bye

exit 0