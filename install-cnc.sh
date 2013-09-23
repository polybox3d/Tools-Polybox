#!/bin/bash


sudo apt-get install python-gtk2 libglade2-dev python-glade2 python-gnome2

#===Fetch===
wget http://static.mah.priv.at/public/xenomai-debs/linux-headers-3.2.21-xenomai+_0.4_i386.deb
wget http://static.mah.priv.at/public/xenomai-debs/linux-image-3.2.21-xenomai+_0.4_i386.deb
#===Install===

sudo dpkg -i linux-headers-3.2.21-xenomai+_0.4_i386.deb
sudo dpkg -i linux-image-3.2.21-xenomai+_0.4_i386.deb

echo "=>Rebooting in 3s..."
sleep 3

sudo reboot