#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh


echoC "$BLU" "Okay, We gonna install patch your kernel with RTAI module.\n"
resetC

sudo apt-get -y install linux-image-3.4-9-rtai-686-pae rtai-modules-3.4-9-rtai-686-pae
print_check_error
sudo apt-get -y install linux-headers-3.4-9-rtai-686-pae
print_check_error

echoC "$ROSE" "You need to restart your computer now."
resetC
