#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

echoC "$BLU" "*******Starting Virtual Serial Port Scrip.*******"
echo "This script install to /usr/sbin/ a script file called virtu-serial."
echo "virtu-serial create two a fake serial port as pty. One should be use as master, and other as slave (even if there is no distinction, since both pty are bidirectional and emulate a serial cable)"
echo "When this is done, we want virtu-serial start as a deamon."
echo "So we copy a deamon skeleton inti /etc/init.d/ and update update-rc to start this deamon (so the main script) at start."
echo "User can manage the script/demaon by using start/stop/restart like all deamon"

resetC

echoC "$BLU" "===>Copy script files"
resetC
sudo cp virtu-serial /usr/sbin/virtu-serial
sudo cp virtu-serial-deamon /etc/init.d/virtu-serial
#give right
sudo chmod +x /etc/init.d/virtu-serial
#update rc file for auto-start at boot
echoC "$BLU" "===>Update RC file"
sudo update-rc.d virtu-serial defaults

print_check_error
print_bye