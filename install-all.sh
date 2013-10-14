#!/bin/bash

MY_DIR=`dirname $0`
state_file=".state_install"
current_state="starting"
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

echoC "$BLU" "#########################################\n
#\n
# Install all script. \n
# -this script will start each install script 1 by 1\n
# Then, get, configure, compile and install tools you need\n
# This script will restart your computer several time\n
# The current state is memorized, so you just need to start this script,\n
# after each restart (from the script)\n
#\n
##########################################\n"

while [[ "$current_state" != "Done" ]]; do

#We check if the script has already been started.
# If yes, we get the current step
    if [[ -e "$state_file" ]]; then
	current_state=`cat $state_file`
    else
	echo starting > "$state_file"
    fi
    echoC "$GREEN" "Etape du script :  $current_state "
    
    
    case $current_state in
	starting )	    
	    echoC "$GREEN" "===>Start the script ? [Y/n] :" ; resetC
	    read start_script
	    if [ "$start_script" != "Y" ]; then
		echoC "$BLU" "Ok then. Bye !"
		resetC
		exit 0
	    fi
	    echo "basic" > $state_file;;
	basic )
	    ./install-basic-all.sh
	    close_if_error
	    echo "cnc-1" > $state_file;;
	cnc-1 )
	    ./install-cnc.sh
	    close_if_error
	    echoC "$ROSE" "~~~~~~~~~~>I'm going to restart your computer"
	    echo "cnc-2" > $state_file
	    echo "You need to restart this script after the reboot to end the installation."
	    resetC
	    echoC "$BlU" "Restart in 10s..."
	    sleep 5
	    echoC "$BlU" "5s..."
	    sleep 5
	    sudo shutdown -r now;;
	    
	cnc-2 )
	    ./install-cnc-2.sh
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
	    echo "setup-env" > $state_file;;
	setup-env )
	    ./setup-environment.sh
	    close_if_error
	    echo "Done" > $state_file;;
	Done )
	    echo "Nothing to do.";;
	* )
	    echo "unknowed state"
	    rm $state_file;;
    esac 
done

print_bye

exit 0




