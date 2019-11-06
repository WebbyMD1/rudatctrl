# Project Title

This project was started to enable control of Mini-Circuits Rudat 6000 programmable RF attenuators. Linux support for these devices is documented but there are few, if any, libraries or applications for Linux. I have developed this simple command line tool to control Rudat 600 attenuators, however it should be a good starting point for other USB attenuators from Mini-Circuits.

## Getting Started

These instructions will let you build, install and execute the rudatctrl command line application.

The code has been tested on Raspberry Pi 2 and 3. It does however NOT work on Raspberry Pi 4. The low level hid_read function call fails on the Pi 4 for unknown reasons.

### Prerequisites

The following components are needed to build the code base

sudo apt-get install libusb-dev libusb-1.0.0-dev libudev-dev libhidapi-dev libserial-dev

In addition you must install the cxxopts header:
git clone https://github.com/jarro2783/cxxopts.git
sudo cp cxxopts/include/cxxopts.hpp /usr/local/include

### Building

The code is so simple a makefile is not necessary. Build using the following command line

g++ -std=c++11 -o rudatctrl -g main.cpp rudat_6000_90_attenuator.cpp -lusb -lhidapi-hidraw

### Installing

sudo ./install.sh

### Examples

Rudatctrl requires low level hardware access, The install script sets up udev rules to accomodate this.

List the serial number of all attached rudat 6000 attenuators:

rudatctrl --list

Read the attenuation of an attenuator

rudatctrl -s 123456789

Set the attenuation of an attenuator to 45 db

rudatctrl -s 123456789 -a 45

## Contributing

Any contributions warmly appreciated. It would be good to hear if this code was useful.

## Authors

Richard Webb of MD1 Technology, Cheltenham Film Studios, Cheltenham.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
