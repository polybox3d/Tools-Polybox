#!/bin/bash


function print_check_error() {
   RET_ERROR=$?
    if [ $RET_ERROR -ne 0 ]; then
	echoC "$RED" "=====>ERROR [$RET_ERROR]. You should check why."
	echo "Script aborted."

	resetC
	exit $RET_ERROR
    else
	echoC "$GREEN" "=====>Done."
	resetC
    fi

 
}

function close_if_error() {
    RET_ERROR=$?
    if [ $RET_ERROR -ne 0 ]; then
	exit $RET_ERROR
    fi
}

function print_bye() {
    echoC "$BLU" "======> End. But you should check everything went well."
    echoC "$GREEN" "=======[ Script end successfuly ! Bye ]======="
    resetC
}