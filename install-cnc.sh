#!/bin/bash


sudo apt-get -y install python-gtk2 libglade2-dev python-glade2 python-gnome2
sudo apt-get -y install libpth-dev tcl8.5-dev tk8.5-dev bwidget libxaw7-dev libncurses-dev python-support libgnomeprintui2.2-dev texlive-lang-cyrillic libudev-dev

cd /tmp/
#===Fetch===
wget http://static.mah.priv.at/public/xenomai-debs/linux-headers-3.2.21-xenomai+_0.4_i386.deb
wget http://static.mah.priv.at/public/xenomai-debs/linux-image-3.2.21-xenomai+_0.4_i386.deb
#===Install===

sudo dpkg -i linux-headers-3.2.21-xenomai+_0.4_i386.deb
sudo dpkg -i linux-image-3.2.21-xenomai+_0.4_i386.deb

echo "=>Rebooting in 3s..."
sleep 3

sudo reboot