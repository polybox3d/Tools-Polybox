#!/bin/bash

OPENCV_VERSION="2.4.7"

sudo apt-get -y install libgtk2.0-0-dev pkg-config libpng-dev libjpeg-dev libtiff-dev libjasper-dev python-dev libavformat-dev libdc1394-22-dev  libcv-dev libcvaux-dev

cd ~/

wget http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/$OPENCV_VERSION/opencv-$OPENCV_VERSION.tar.gz

tar -xvf opencv-$OPENCV_VERSION.tar.gz

rm -r opencv-$OPENCV_VERSION.tar.gz
cd opencv-$OPENCV_VERSION/
mkdir build
cd build

cmake -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
make -j 2
sudo make install
sudo ldconfig
cd ~/
