#!/bin/bash

MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

echoC "$BLU" "#########################################\n
#\n
# Install PolyBox Software\n
# \n
##########################################\n"
resetC

cd ~/
git clone https://github.com/skapin/polybox.git
cd polybox
git submodule update --init --recursive
cd ~/

print_bye
resetC

