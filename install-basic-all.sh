#!/bin/bash



echo "===>install basic paquages"
sudo apt-get update

sudo apt-get install git subversion emacs geany vim gcc g++ php5-dev python cmake git-core git-gui dpkg-dev
echo "*Tools: "

sudo apt-get install vlc firefox picocom 

echo "*Documentation: "
sudo apt-get install dvipng texlive-extra-utils texlive-latex-recommended texlive-fonts-recommended ghostscript imagemagick texlive-lang-french texlive-lang-german texlive-lang-spanish texlive-lang-polish texlive-font-utils asciidoc texlive-latex-extra  asciidoc source-highlight dblatex

echo "*Lib: "
sudo apt-get install devscripts debhelper dh-kpatches findutils build-essential
sudo apt-get install libreadline-dev xsltproc groff python-lxml libglu1-mesa-dev libgl1-mesa-dev libglib2.0-dev libgtk2.0-dev
sudo apt-get install libeigen3-dev build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk
sudo apt-get install libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common
sudo apt-get install libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libpulse-dev

echo "*Qt: "
#Qt5.x
sudo apt-add-repository ppa:ubuntu-sdk-team/ppa
sudo apt-get update
sudo apt-get install qtdeclarative5-dev
sudo apt-get install qtmobility-dev
sudo apt-get install qt5-default qttools5-dev-tools qtmultimedia5-dev libqt5opengl5-dev
#Qt4.x
sudo apt-get install libqt4-dev qt4-qmake r-base-dev libcurl4-gnutls-dev
sudo apt-get install libqt4-dev libphonon-dev libqt4-opengl-dev libqt4-opengl

sudo apt-get install freeglut3 freeglut3-dev
sudo apt-get install mesa-common-dev
