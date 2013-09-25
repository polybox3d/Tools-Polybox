#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

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

sudo apt-get -y install python-gtk2 libglade2-dev python-glade2 python-gnome2
print_check_error
sudo apt-get -y install libpth-dev tcl8.5-dev tk8.5-dev bwidget libxaw7-dev libncurses-dev python-support libgnomeprintui2.2-dev texlive-lang-cyrillic libudev-dev
print_check_error

cd /tmp/
#===Fetch===
wget http://static.mah.priv.at/public/xenomai-debs/linux-headers-3.2.21-xenomai+_0.4_i386.deb
print_check_error
wget http://static.mah.priv.at/public/xenomai-debs/linux-image-3.2.21-xenomai+_0.4_i386.deb
print_check_error
#===Install===

sudo dpkg -i linux-headers-3.2.21-xenomai+_0.4_i386.deb
print_check_error
sudo dpkg -i linux-image-3.2.21-xenomai+_0.4_i386.deb
print_check_error

print_bye

echoC "$ROSE" "You need to restart your computer now."
resetC

