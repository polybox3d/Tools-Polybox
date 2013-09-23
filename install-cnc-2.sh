#!/bin/bash

#===Fetch===
wget http://static.mah.priv.at/public/xenomai-debs/libxenomai1_2.6.1_i386.deb
wget http://static.mah.priv.at/public/xenomai-debs/libxenomai-dev_2.6.1_i386.deb

#===Install After rebbot and Xenomai up===

sudo dpkg -i libxenomai1_2.6.1_i386.deb
sudo dpkg -i libxenomai-dev_2.6.1_i386.deb
sudo dpkg -i xenomai-runtime_2.6.1_i386.deb

#===Get and install LinuxCNC===

git clone git://git.mah.priv.at/emc2-dev.git linuxcnc-rtos
cd linuxcnc-rtos
#By default, you will get files from "master", which is not what we want - there is a good branch: 
git branch --track rtos-integration-preview3 origin/rtos-integration-preview3
git checkout rtos-integration-preview3

#Install the build dependencies - this will pull in all packages required to compile linuxcnc:
cd debian
./configure sim
cd ..
#This will show a list of packages missing (if any)
dpkg-checkbuilddeps

#===Add right===
sudo adduser "$USER" xenomai
sudo adduser "$USER" kmem

sudo rmmod lp

#===Start Tests===
. ../scripts/rip-environment
runtests
latency-test


echo "End."



