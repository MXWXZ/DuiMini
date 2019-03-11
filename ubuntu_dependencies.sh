#!/bin/sh
echo  We need sudo permission...

# sfml-window
sudo apt-get install libx11-dev -y
sudo apt-get install libxcb1-dev -y
sudo apt-get install libx11-xcb-dev -y
sudo apt-get install libxcb-randr0-dev -y
sudo apt-get install libxcb-image0-dev -y
sudo apt-get install libxrandr-dev -y
sudo apt-get install libgl1-mesa-dev -y
sudo apt-get install libudev-dev -y
sudo apt-get install libxrandr-dev -y

# sfml-graphics
sudo apt-get install libfreetype6-dev -y
sudo apt-get install libjpeg-dev -y

# sfml-audio
sudo apt-get install libopenal-dev -y
sudo apt-get install libflac-dev -y
sudo apt-get install libvorbis-dev -y