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

#===Get and install LinuxCNC===
cd ~/
git clone https://github.com/zultron/linuxcnc.git $LINUX_CNC_FOLDER
cd $LINUX_CNC_FOLDER

#Install the build dependencies - this will pull in all packages required to compile linuxcnc:
cd debian
./configure -a
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
sudo make log

#we blacklist lp module....
sudo sh -c 'echo "blacklist lp" >> /etc/modprobe.d/blacklist.conf'
sudo update-initramfs -u
cp -R polybox-milling-conf cd~/$LINUX_CNC_FOLDER/configs/Polybox-v1
#===Start Tests===
. ../scripts/rip-environment
runtests
latency-test



echo "End."



