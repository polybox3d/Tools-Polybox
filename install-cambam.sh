#!/bin/bash
#########################################
#
# CamBam install script. 
# Install, compile and configure CamBam
#
##########################################
SCAN_LASER_DIR="FabScan100"

MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

echoC "$BLU" "=====CamBam 3D"
resetC
cd ~/

wget http://www.cambam.co.uk/downloads/dw/CamBam0.9.8N-mono-beta5.tgz
print_check_error
tar -xvf CamBam0.9.8N-mono-beta5.tgz
print_check_error
mv CamBam0.9.8 CamBam


print_bye

exit 0