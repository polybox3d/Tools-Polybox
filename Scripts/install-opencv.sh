#!/bin/bash
#########################################
#
# OpenCV script. 
# Used to install OpenCV and related packaged
#
##########################################
MY_DIR=`dirname $0`
source $MY_DIR/bin/color.sh
source $MY_DIR/bin/utils.sh


echoC "$BLU" ">>>Install requiered packages "
resetC

sudo apt-get -y install libgtk2.0-dev pkg-config libpng-dev libjpeg-dev libtiff-dev libjasper-dev python-dev libdc1394-22-dev 
#libavformat-dev  libcv-dev libcvaux-dev
print_check_error
sudo apt-get install libboost-all-dev libeigen3-dev libflann-dev libusb-dev libusb-1.0-0-dev libvtk5.8 libvtk5.8-qt4 liblz4-dev libqt5multimedia5-plugins
print_check_error

echoC "$BLU" ">>> Install FLANN "
resetC

cd ~/
wget http://people.cs.ubc.ca/%7Emariusm/uploads/FLANN/flann-1.8.4-src.zip
print_check_error

unzip flann-1.8.4-src.zip
cd flann-1.8.4-src/ 
print_check_error

mkdir build && cd build/
cd build
print_check_error

cmake ..
print_check_error

make 
print_check_error

sudo make install
print_check_error



echoC "$BLU" ">>> Install PCL "
resetC
cd ~/
git clone https://github.com/PointCloudLibrary/pcl
cd pcl
print_check_error
mkdir build
cd build
cmake ..
print_check_error
make
print_check_error
sudo make install
print_check_error


#wget http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/$OPENCV_VERSION/opencv-$OPENCV_VERSION.tar.gz
#tar -xvf opencv-$OPENCV_VERSION.tar.gz
#rm -r opencv-$OPENCV_VERSION.tar.gz
#cd opencv-$OPENCV_VERSION/

cd ~/
git clone https://github.com/Itseez/opencv opencv-3.0
print_check_error
cd opencv-3.0
mkdir build
cd build
print_check_error

echoC "$BLU" ">>>Building... "
resetC
cmake -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
print_check_error

make -j 2
print_check_error

sudo make install
print_check_error

sudo ldconfig
print_check_error
