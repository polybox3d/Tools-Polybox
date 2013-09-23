#!/bin/bash

echo "=====Scanner 3D"

sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
sudo apt-get update
sudo apt-get install libpcl-all
sudo apt-get install uvccapture
sudo adduser "$USER" dialout


#======FAB SCAN100======
cd ~/
git clone git://github.com/francisengelmann/FabScan100.git
cd FabScan100