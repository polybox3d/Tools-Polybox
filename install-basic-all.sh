#!/bin/bash
#########################################
#
# Basic script. 
# Used to install and setup basic tools and
# lib on your computer. Like Qt, vlc or git.
#
##########################################
MY_DIR=`dirname $0`
source $MY_DIR/color.sh
source $MY_DIR/utils.sh

echoC "$BLU" "*******Starting Basic installation Script.*******"
echo "This script will install and update some basics tools and libs."
echo "You computer will be updated."
echo "This can be take some time. You can go drink a coffe since everything is automatic,"
echo "but you should, at least, check everything went okay at the end"

echoC "$GREEN" "===>Start the script ? [Y/n] :"
read start_script
if [ "$start_script" != "Y" ]; then
    echoC "$BLU" "Ok then. Bye !"
    resetC
    exit 0
fi
echoC "$BLU" "===>Install basics paquages..." 
resetC

sudo apt-get update
sudo apt-get -y install git subversion emacs geany vim gcc g++ php5-dev python cmake git-core git-gui dpkg-dev
print_check_error
echoC "$BLU" "*Tools: "
resetC

sudo apt-get -y install vlc firefox picocom xinput_calibrator glade python-setuptools
print_check_error

echoC "$BLU" "*Documentation: "
resetC

sudo apt-get -y install dvipng texlive-extra-utils texlive-latex-recommended texlive-fonts-recommended ghostscript imagemagick texlive-lang-french texlive-lang-german texlive-lang-spanish texlive-lang-polish texlive-font-utils asciidoc texlive-latex-extra  asciidoc source-highlight dblatex
print_check_error

echoC "$BLU" "*Lib: "
resetC

sudo apt-get -y install devscripts debhelper dh-kpatches findutils build-essential libreadline-dev xsltproc groff python-lxml libglu1-mesa-dev libgl1-mesa-dev libglib2.0-dev libgtk2.0-dev python-gtksourceview2 python-gnome2-desktop-dev python-gnome2-extras-dev python-xlib
print_check_error

sudo apt-get -y install libeigen3-dev build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common python-gtkglext1 python-vte
print_check_error

sudo easy_install py-notify


sudo apt-get -y install libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libpulse-dev
print_check_error

echoC "$BLU" "*Qt: "
resetC
#Qt5.x
sudo apt-add-repository -y ppa:ubuntu-sdk-team/ppa
print_check_error

sudo apt-get -y update
print_check_error

sudo apt-get -y install qtdeclarative5-dev qtmobility-dev
print_check_error
sudo apt-get -y install qt5-default qttools5-dev-tools qtmultimedia5-dev libqt5opengl5-dev mesa-common-dev qtcreator
print_check_error
#Qt4.x
#sudo apt-get install libqt4-dev qt4-qmake r-base-dev libcurl4-gnutls-dev
#sudo apt-get install libqt4-dev libphonon-dev libqt4-opengl-dev libqt4-opengl

#sudo apt-get install freeglut3 freeglut3-dev
print_bye

exit 0