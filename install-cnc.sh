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
sudo apt-get -y install libpth-dev tcl8.5-dev tk8.5-dev bwidget libxaw7-dev libncurses-dev python-support libgnomeprintui2.2-dev texlive-lang-cyrillic libudev-dev libtk-dev zlib1g-dev
print_check_error


echoC "$BLU" "\n
#########################################################\n
# Xenomai Kernel Packages\n
# John Morris (zultron on freenode) has put up package \n
# repositories containing Xenomai packages for\n
#  Precise, Squeeze and Lucid. \n
#\n
# Special thanks to him and his team. Really !\n
#########################################################\n"

# Set CODENAME as appropriate for your environment
# should be one of 'precise', 'lucid', 'squeeze'; set manually if you get something different
CODENAME=$(lsb_release -cs); echo $CODENAME
# Add the repository to /etc/apt/sources.list
echo "deb http://deb.machinekit.net/$CODENAME $CODENAME main" | sudo tee -a /etc/apt/sources.list 
print_check_error
echo "deb-src http://deb.machinekit.net/$CODENAME $CODENAME main" | sudo tee -a /etc/apt/sources.list
print_check_error
# update the package list
sudo apt-get update
# Install the package containing the signing keys; answer 'y' to install despite missing keys
sudo apt-get -y install zultron-keyring
print_check_error
# Install the xenomai run-time tools and headers (for building LCNC)
sudo apt-get -y install xenomai-runtime libxenomai-dev
print_check_error
# Install the xenomai-patched kernel
sudo apt-get -y install linux-image-3.5.7-xenomai-2.6.2.1
print_check_error

#########################################################
#          RealTek r8168 NIC chipset problems  
#
# The r8169 driver is finicky when driving an r8168 NIC,
# and won't drive it at 1Gb in any case. 
# The Xenomai patches break it entirely.
#########################################################

r8169=`lspci | grep 8168 | wc -l`

# does the computer need this driver ??
if [ "$r8169" != "0" ]; then
    sudo apt-get -y install kmod-r8168-modules-3.5.7-xenomai-2.6.2.1
    sudo update-initramfs -u -k 3.5.7-xenomai-2.6.2.1
    print_check_error
fi
#===Add right===
sudo adduser "$USER" xenomai
sudo adduser "$USER" kmem
    
print_bye

echoC "$ROSE" "You need to restart your computer now."
resetC

