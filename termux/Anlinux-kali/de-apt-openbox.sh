#!/bin/bash

#Get the necessary components
apt-get update
apt-get install openbox xterm -y
apt install tigervnc-common tigervnc-scraping-server tigervnc-standalone-server tigervnc-xorg-extension -y
apt-get install thunar mate-terminal xfce4-panel -y

#Setup the necessary files
mkdir ~/.vnc
cd ./xstartup -P ~/.vnc/
cd ./vncserver-start -P /usr/local/bin/
cd ./vncserver-stop /usr/local/bin/

chmod +x ~/.vnc/xstartup
chmod +x /usr/local/bin/vncserver-start
chmod +x /usr/local/bin/vncserver-stop

echo " "
echo "You can now start vncserver by running vncserver-start"
echo " "
echo "It will ask you to enter a password when first time starting it."
echo " "
echo "The VNC Server will be started at 127.0.0.1:5901"
echo " "
echo "You can connect to this address with a VNC Viewer you prefer"
echo " "
echo "Connect to this address will open a window with Awesome Window Manager"
echo " "
echo " "
echo " "
echo "Running vncserver-start"
echo " "
echo " "
echo " "
echo "To Kill VNC Server just run vncserver-stop"
echo " "
echo " "
echo " "

echo "export DISPLAY=":1"" >> /etc/profile
apt install apt-utils aptitude -y 
apt install codeblocks build-essential -y 
apt install pavucontrol pulseaudio glade -y
apt install gedit firefox-esr audacious -y
apt install brasero atril synaptic -y
apt install gnome-core-devel -y

vncserver-start