#!/bin/sh 

GREEN="\\033[1;32m" 
RESET="\\033[0;39m" 
RED="\\033[1;31m" 
ROSE="\\033[1;35m" 
BLU="\\033[1;34m" 
WHITE="\\033[0;02m" 
GRAY="\\033[1;08m" 
YELLOW="\\033[1;33m" 
CYAN="\\033[1;36m"


function echoC() {
    echo -e "$1" "$2"
}

function resetC() {
    echoC "$RESET" ""
}
