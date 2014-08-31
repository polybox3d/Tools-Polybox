#!/bin/bash
#########################################
#
# Scanner install script. 
# Install, compile and configure scanning software
#
##########################################

MY_DIR=`dirname $0`
source $MY_DIR/bin/color.sh
source $MY_DIR/bin/utils.sh

echoC "$BLU" "=====Scanner 3D"
resetC

sudo add-apt-repository -y ppa:v-launchpad-jochen-sprickerhof-de/pcl
sudo apt-get -y update
print_check_error
sudo apt-get -y install libpcl-all uvccapture
print_check_error
sudo adduser "$USER" dialout

exit 0
