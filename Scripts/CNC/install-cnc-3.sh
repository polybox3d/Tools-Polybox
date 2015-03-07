#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh

LINUX_CNC_FOLDER=~/linuxcnc

echoC "$GREEN" "Okay, We gonna check your kernel and LinuxCNC !.\n"
resetC

#Is your kernel patched ? (real time with RTAI)
if [ `uname -r |grep rtai | wc -l` -gt 0  ];
then
    echo "======> Your kernel is patched for RealTime with RTAI. I'm goint to process LinuxCNC installation and configuration now."
else
    echo "======> I can't execute this script. Your kernel need to be patched for realTime by RTAI."
    echo "======> install another kernel, or switch branch from Git repo"
    exit 0
fi

#===Copy miling configuration file===
mkdir $LINUX_CNC_FOLDER
print_check_error
mkdir $LINUX_CNC_FOLDER/configs/
print_check_error
cp -R ../../polybox-milling-conf/ $LINUX_CNC_FOLDER/configs/Polybox/
