#!/bin/bash

#Get the necessary components
apt-get update
apt-get install openssh-server -y

#Setup the necessary files
cp ./sshd_config /etc/ssh

echo "You can now start OpenSSH Server by running /etc/init.d/ssh start"
echo " "
echo "The Open Server will be started at 127.0.0.1:22"

#Get the necessary components
apt-get install xfce4 xfce4-terminal -y
apt-get install tightvncserver dbus-x11  -y
apt-get install xfe -y

#Setup the necessary files
mkdir ~/.vnc
cp /xstartup ~/.vnc/
cp /vncserver-start /usr/local/bin/
cp /vncserver-stop /usr/local/bin/

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
echo "Connect to this address will open a window with Mate Desktop Environment"
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
source /etc/profile


apt-get install htop vim -y

vncserver-start
