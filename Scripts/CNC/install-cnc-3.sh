#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh

LINUX_CNC_FOLDER=~/linuxcnc

echoC "$GREEN" "Okay, We gonna check your kernel and install LinuxCNC !.\n"
resetC

#Is your kernel patched ? (real time with RTAI)
if [ `uname -r |grep rtai | wc -l` -gt 0  ];
then
    echo "======> Your kernel is patched for RealTime with RTAI. I'm goint to process LinuxCNC installation and configuration now."
else
    echo "======> I can't execute this script. Your kernel need to be patched for realTime by RTAI."
    echo "======> Try to execute ./install-cnc.sh 1st."
    exit 0
fi



echoC "$BLU" "##############################################################\n
We need to create a file called /etc/apt/sources.list.d/linuxcnc-buildbot.list ,\n
containing one of these lines (depending on which version of linuxcnc you want): \n\n
    deb http://buildbot.linuxcnc.org precise 2.6-rt \n
    deb http://buildbot.linuxcnc.org precise master-rt \n
    deb http://buildbot.linuxcnc.org precise v2.5_branch-rt \n\n
The current lastest stable version is 2.5. (Jul 2014)\n
##########################################\n"
resetC

sudo sh -c 'echo "deb http://buildbot.linuxcnc.org precise v2.5_branch-rt" >> /etc/apt/sources.list.d/linuxcnc-buildbot.list'

sudo apt-get -y update
sudo apt-get -y --force-yesinstall linuxcnc
print_check_error

#===Copy miling configuration file===
mkdir $LINUX_CNC_FOLDER
mkdir $LINUX_CNC_FOLDER/configs/
cp -R ../../polybox-milling-conf $LINUX_CNC_FOLDER/configs/Polybox-v1
