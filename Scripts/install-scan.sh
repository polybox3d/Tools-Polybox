#!/bin/bash
#########################################
#
# Scanner install script. 
# Install, compile and configure scanning software
#
##########################################

MY_DIR=`dirname $0`
source $MY_DIR/bin/color.sh
source $MY_DIR/bin/utils.sh

echoC "$BLU" "=====Scanner 3D"
resetC
sudo adduser "$USER" dialout


echoC "$GREEN" "*******************"
echo  " Out of date script. Nothing to do. "
echo "Continue."
echo "*******************"
resetC

print_bye

exit 0
## for Debian
if [ `lsb_release -d | grep Debian | wc -l` -gt 0  ];
then
	sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-key 19274DEF
	sudo sh -c 'echo "deb http://ppa.launchpad.net/v-launchpad-jochen-sprickerhof-de/pcl/ubuntu maverick main" > /etc/apt/sources.list.d/pcl.list'
	sudo apt-get update
	sudo apt-get  -t wheezy-backports -y install libpcl-all	uvccapture
	print_check_error

## for Ubuntu
elif [ `lsb_release -d | grep Ubuntu | wc -l` -gt 0  ];	
then
	sudo add-apt-repository -y ppa:v-launchpad-jochen-sprickerhof-de/pcl
	sudo apt-get -y update
	print_check_error
	sudo apt-get -y install libpcl-all uvccapture
	print_check_error
else
	echoC "$RED" "=====>ERROR. You are not using Debian or Ubuntu... We don't know how ot install PCL package on your OS"
	echo "Script aborted."
	resetC
	exit 1
fi


exit 0
