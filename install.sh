#!/bin/bash
#
# This simple script should install the dependancies, build and install rudatctrl
#
sudo apt-get install libusb-dev libusb-1.0.0-dev libudev-dev libhidapi-dev libserial-dev
g++ -std=c++11 -o rudatctrl -g main.cpp rudat_6000_90_attenuator.cpp -lusb -lhidapi-hidraw
sudo cp rudatctrl /usr/local/bin
sudo cp 85-rudat.rules /etc/udev/rules.d/
