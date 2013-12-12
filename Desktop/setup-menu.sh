#!/bin/bash

# Setup Meny entries for Polybox

xdg-desktop-menu install polybox-polybox.directory polybox-cnc.directory polybox-cnc.desktop CNC-gmoccapy.desktop CNC-gscreen.desktop CNC-pyvcp.desktop CNC-linuxcnc.desktop

xdg-desktop-menu install polybox-polybox.directory polybox-tools.directory polybox-tools-getmakers.desktop polybox-tools-thingiverse.desktop polybox-tools-shapeways.desktop polybox-tools-sculpteo.desktop

xdg-desktop-menu install polybox-polybox.directory polybox-polybox.desktop
#xdg-desktop-menu install polybox-polybox.directory polybox-help.directory

xdg-icon-resource install --size 22 ./icon/polybox.png polybox-polybox-menu