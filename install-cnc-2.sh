#!/bin/bash

LINUX_CNC_FOLDER=linuxcnc
#Is your kernel patched ? (real time with Xenomai)
if [ `uname -r |grep xenomai | wc -l` -gt 0  ];
then
    echo "======> Your kernel is patched for RealTime. I'm goint to process LinuxCNC installation and configuration now."
else
    echo "======> I can't execute this script. Your kernel need to be patched fro realTime by Xenomai."
    echo "======> Try to execute ./install-cnc.sh 1st."
    exit 0
fi


cd /tmp/
#===Fetch===
wget http://static.mah.priv.at/public/xenomai-debs/libxenomai1_2.6.1_i386.deb
wget http://static.mah.priv.at/public/xenomai-debs/libxenomai-dev_2.6.1_i386.deb
wget http://static.mah.priv.at/public/xenomai-debs/xenomai-runtime_2.6.1_i386.deb
#===Install After rebbot and Xenomai up===

sudo dpkg -i libxenomai1_2.6.1_i386.deb
sudo dpkg -i libxenomai-dev_2.6.1_i386.deb
sudo dpkg -i xenomai-runtime_2.6.1_i386.deb

#===Get and install LinuxCNC===
cd ~/
git clone git://git.mah.priv.at/emc2-dev.git $LINUX_CNC_FOLDER
cd linuxcnc
#By default, you will get files from "master", which is not what we want - there is a good branch: 
git branch --track rtos-integration-preview3 origin/rtos-integration-preview3
git checkout rtos-integration-preview3

#Install the build dependencies - this will pull in all packages required to compile linuxcnc:
cd debian
./configure sim
cd ..
#This will show a list of packages missing (if any)
dpkg-checkbuilddeps

#===Compile and config LinuxCNC===
cd src
sh autogen.sh
./configure 
if [ $? -ne 0 ]; then
    echo "=========>./configure command ERROR : $retval"
    echo "=========> Stop.]"
    exit
fi
make
if [ $? -ne 0 ]; then
    echo "=========>make command ERROR : $retval"
    echo "=========> Stop.]"
    exit
fi
sudo make setuid
#===Add right===
sudo adduser "$USER" xenomai
sudo adduser "$USER" kmem

#we blacklist lp module....
sudo sh -c 'echo "blacklist lp" >> /etc/modprobe.d/blacklist.conf'
sudo update-initramfs -u
cp -R polybox-milling-conf cd~/$LINUX_CNC_FOLDER/configs/Polybox-v1
#===Start Tests===
. ../scripts/rip-environment
runtests
latency-test



echo "End."



