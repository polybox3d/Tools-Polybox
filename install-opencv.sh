#!/bin/bash


#sudo apt-get -y install libgtk2.0-0-dev pkg-config libpng-dev libjpeg-dev libtiff-dev libjasper-dev python-dev libavformat-dev libdc1394-22-dev  libcv-dev libcvaux-dev

cd ~/

#wget http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.6/opencv-2.4.6.tar.gz

tar -xvf opencv-2.4.6.tar.gz

rm -r opencv-2.4.6.tar.gz
cd opencv-2.4.6/
mkdir build
cd build

cmake ..
make -j 2
sudo make install
sudo ldconfig
cd ~/