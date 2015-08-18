#!/bin/bash

MY_DIR=`dirname $0`
state_file=".state_install"
current_state="starting"
source $MY_DIR/bin/color.sh
source $MY_DIR/bin/utils.sh

echoC "$BLU" "#########################################\n
#\n
# Install all script. \n
# Tested For Debian 7 (Wheezy), but can works on Ubuntu 12.04 LTS with minor changes
# -this script will start each install script 1 by 1\n
# Then, get, configure, compile and install tools you need\n
# This script will restart your computer several time\n
# The current state is memorized, so you just need to start this script,\n
# after each restart (from the script)\n
#\n
##########################################\n"

# check OS
if [ `lsb_release -d | grep Debian | wc -l` -gt 0  ];
then
	echoC "$GREEN" "===> You are Using Debian OS :" 
	resetC
elif [ `lsb_release -d | grep Ubuntu | wc -l` -gt 0  ];	
then
	echoC "$GREEN" "===> You are Using Ubuntu OS :" 
	resetC
else
	echoC "$RED" "=====>ERROR. You are not using Debian 32b or Ubuntu 32b ..."
	echo "Script aborted."
	resetC
fi


while [[ "$current_state" != "Done" ]]; do

#We check if the script has already been started.
# If yes, we get the current step
    if [[ -e "$state_file" ]]; then
	current_state=`cat $state_file`
    else
	echo starting > "$state_file"
    fi
    echoC "$GREEN" "Etape du script :  $current_state "
    resetC
    
    case $current_state in
	starting )	    
	    echoC "$GREEN" "===>Start the script ? [Y/n] :" ; resetC
	    read start_script
	    if [ "$start_script" != "Y" ]; then
		echoC "$BLU" "Ok then. Bye !"
		resetC
		exit 0
	    fi
	    #setup APT variable. Force-yes and -yes
	    sudo sh -c 'echo "APT::Get::Assume-Yes "true";\nAPT::Get::force-yes "true";" >> /etc/apt/apt.conf.d/90forceyes'
	    echo "basic" > $state_file;;
	basic )
	    ./install-basic-all.sh
	    close_if_error
	    ./install-opencv.sh
	    close_if_error
	    echo "cnc-1" > $state_file;;
	cnc-1 )
	    ./CNC/install-cnc.sh
	    close_if_error
	    echo "cnc-3" > $state_file;;
	cnc-3 )
	    ./CNC/install-cnc-3.sh
	    close_if_error
	    ./install-cambam.sh
	    close_if_error
	    echo "scan" > $state_file;;
	scan )
	    ./install-opencv.sh
	    close_if_error
	    ./install-scan.sh
	    close_if_error
	    echo "printer" > $state_file;;
	printer )
	    ./install-printer.sh
	    close_if_error
	    echo "polybox" > $state_file;;
	polybox )
	    ./install-polyboxSoftware.sh
	    close_if_error
	    echo "setup-env" > $state_file;;
	setup-env )
	    ./Environment/setup-environment.sh
	    close_if_error
	    sudo rm /etc/apt/apt.conf.d/90forceyes
	    echo "Done" > $state_file;;
	Done )
	    echo "Nothing to do.";;
	* )
	    echo "unknowed state"
	    rm $state_file;;
    esac 
done

print_bye

echoC "$ROSE" "**************************************"
echo ""
echo "Okay ! Your computer is ready and fully setup."
echo "You should restart it to end the process."
echo ""
echo "**************************************"
echo ""
resetC

exit 0




