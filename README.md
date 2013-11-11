Tools-Polybox
=============

You can find several script to help you install and configure your tools.

If you start with a fresh 12.04 Ubuntu, just start the main script :

./install-all.sh


This script will start each installation and setup script 1 by 1. YOu mostly can watch, cause you need to do nothing.

This script will restart your computer. 
YOU need to RESTART this main script after each reboot, till the script end.
It's very important. If you dont restart the script, no magic will happends and you will miss some important part.


=======
JoypadOverlay
=============

JoypadOverlay can be use to affect action to specific joypad controler.


src/config/ fodler emabbed joypad file, such as configuration image or actions.
You need to copy this folder inside the build directory (for example .../build/Debug  or  .../build/Release)

