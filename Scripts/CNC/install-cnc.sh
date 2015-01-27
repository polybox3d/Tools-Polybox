#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/../bin/color.sh
source $MY_DIR/../bin/utils.sh

echoC "$BLU" "#########################################\n
#\n
# Install Linux CNC\n
# \n
# This script will install some part of LinuxCNC for you \n
# To use LinuxCNC, a real-time kernel is needed \n
# For this reaason, your Linux kernel will be patched by Xenomai \n
# A reboot is needed at the end \n
# Then, after the reboot, you need to start the 2nd CNC script \n
# If you use the installer, just restart it, and watch. \n
#\n
##########################################\n"
resetC

sudo apt-get -y install python-gtk2 libglade2-dev python-glade2 python-gnome2 python-pip python-dev build-essential
print_check_error
sudo apt-get -y install libpth-dev tcl8.5-dev tk8.5-dev bwidget libxaw7-dev libncurses-dev python-support libgnomeprintui2.2-dev texlive-lang-cyrillic libudev-dev zlib1g-dev libtk-img libmodbus-dev
print_check_error
sudo apt-get -y install libboost-python-dev tk-dev tcl-dev 
print_check_error
sudo pip install ino
print_check_error

echoC "$BLU" "\n
#########################################################\n
# RTAI Kernel Packages\n
# SebKuzminsky & LinuxCNC team \n
#  For Ubuntu 12.04.4 Precise \n
#\n
# Special thanks to him and his team. Really !\n\n
# Link: http://wiki.linuxcnc.org/cgi-bin/wiki.pl?LinuxCNC_On_Ubuntu_Precise
# Date: Jul 2014
#########################################################\n"
resetC

#bring the machine up to date with the latest packages in Ubuntu Precise. 
sudo apt-get update
sudo apt-get dist-upgrade
print_check_error
#Create a file called /etc/apt/sources.list.d/linuxcnc.list, containing the line: deb http://linuxcnc.org precise base
sudo sh -c 'echo "deb http://linuxcnc.org precise base" >> /etc/apt/sources.list.d/linuxcnc.list'
#Add the LinuxCNC Archive Signing Key to your apt keyring
sudo apt-key adv --keyserver hkp://keys.gnupg.net --recv-key 8f374fef
sudo apt-get update
#REBOOT
sudo adduser "$USER" kmem
    
print_bye

echoC "$ROSE" "You need to restart your computer now."
resetC

