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
cd src/
/usr/lib/i386-linux-gnu/qt5/bin/qmake
print_check_error
make
print_check_error

cd $MY_DIR
echo "git pull ~/polybox/" >> git-update.sh

print_bye
resetC

