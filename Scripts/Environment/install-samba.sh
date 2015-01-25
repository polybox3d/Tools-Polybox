#!/bin/bash

MY_DIR=`dirname $0`

source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh


echoC "$BLU" "#########################################\n
#\n
# Install all script. \n
# -this script will start each install script 1 by 1\n
# Then, get, configure, compile and install tools you need\n
# This script will restart your computer several time\n
# The current state is memorized, so you just need to start this script,\n
# after each restart (from the script)\n
#\n
##########################################\n"
resetC
sudo apt-get -y install samba
print_check_error

cp -R $MY_DIR/../../plbx-dropbox/ ~/
chmod -R 777 ~/plbx-dropbox

sudo sh -c 'echo "
[plbx-dropbox]
   path = $HOME/plbx-dropbox
   comment = Shared folder for Polybox.
   read only = no
   guest ok = yes
   public = yes
" >> /etc/samba/smb.conf'
print_check_error

print_bye
