#!/bin/bash
#########################################
#
# Printer script. 
# Install printer software and firmware
#
##########################################
MY_DIR=`dirname $0`
source $MY_DIR/bin/color.sh
source $MY_DIR/bin/utils.sh

PRINTRUNDIR="$HOME/Printrun"
SKEINFORGEDIR="$PRINTRUNDIR/skeinforge"

echoC "$BLU" "*******Starting Printer installation Script.*******"
echo "This script will install prinetr software."


echoC "$BLU" "===>Get and configure Mono..." 
resetC
sudo apt-get -y install mono-complete
print_check_error

echoC "$BLU" "===>Download Printer Software..." 
resetC

cd ~
# http://www.repetier.com/download-now/
# Repetier-Host Linux 1.0.6 
# If you like Repetier, you should donate !
echoC "$GREEN" "==========================================================" 
echo " The script will now download Repetier-Host for Linux."
echo " Repetier-Host is an opensource software for 3D printer. It allows the user to print STL file and visualize the evolution of the print." 
echo -e "This is NOT a Polybox3D software. If you wish to support the further development of this free software to obtain updates and new features\n in future, we would appreciate a voluntary donation. Donate quick and easy via PayPal, simply enter the desired amount" 
echo "________________________________________" 
echo " * Web Site http://www.repetier.com/"
echo " * Repetier-Host Linux 1.0.6"
echo " * Donate :  http://www.repetier.com/download-software/"
echo "==========================================================" 
resetC

wget -O repetierHostLinux.tgz 'http://www.repetier.com/w/?wpdmdl=1785'
tar -xzf repetierHostLinux.tgz
print_check_error
cd RepetierHost
print_check_error
sh configureFirst.sh
print_check_error


sudo usermod -a -G dialout $(whoami)


echoC "$BLU" "===>Download Printer Softwer (printrun)..." 
resetC


cd $HOME
echo "Removing existing Printrun directory..."
rm -rf $PRINTRUNDIR
echo "Cloning Printrun..."
git clone https://github.com/kliment/Printrun.git
echo "Grabbing skeinforge..."
wget -P /tmp http://fabmetheus.crsndoo.com/files/41_reprap_python_beanshell.zip
echo "Unzipping skeinforge into Printrun directory..."
unzip -d $SKEINFORGEDIR /tmp/41_reprap_python_beanshell.zip
echo "Symlinking skeinforge inside Printrun directory..."
ln -s $SKEINFORGEDIR/* $PRINTRUNDIR/
echo "Cleaning up temporary installation files..."
rm -rf /tmp/41_reprap_python_beanshell.zip


cd ~
echoC "$BLU" "===>Download Cura..." 
resetC
echoC "$ROSE" "---[Version: 15.02.1]---" 
resetC
wget https://software.ultimaker.com/current/cura_15.02.1-debian_i386.deb
sudo dpkg -i cura_15.02.1-debian_i386.deb
rm cura_15.02.1-debian_i386.deb


echoC "$BLU" "===>Download Printer Firmware..." 
resetC
cd ~
git clone https://github.com/skapin/Repetier-Firmware.git




print_bye

exit 0
