#!/bin/sh

echo "Prepare env"
IMG_DIR="/etc/eletrohorse-img/"
APP_DIR="/usr/bin/"
SYSTEMD_PATH="/lib/systemd/system/"

tree -L 2

sudo systemctl stop board.service
sudo pkill phython3

#cvt  1024 600 60
#Prepare display settings and activate 1-wire interface
sudo cp $HOME/env/config.txt /boot/config.txt

echo "Prepare env .... OK"
sudo apt update
sudo apt install python3 idle3
python3 -m pip install python-dev-tools --user --upgrade

echo "Install Program Dependencies .... OK"
pip3 install opencv-python
pip3 install pynput

sudo apt-get install -y libatlas-base-dev libhdf5-dev libhdf5-serial-dev libatlas-base-dev libjasper-dev  libqtgui4  libqt4-test
sudo apt-get install python3-pil python3-pil.imagetk
sudo apt install tmux
sudo apt-get install x11-utils

#Prepare display app to auto start after boot
if [ ! -d $HOME/.config/autostart/ ]; then
    sudo mkdir -p $HOME/.config/autostart/
fi

sudo cp $HOME/env/systemd/display.desktop $HOME/.config/autostart/

if [ ! -d $IMG_DIR ]; then
    sudo mkdir -p $IMG_DIR
fi

#Copy images program
sudo cp -r $HOME/env/image/*     $IMG_DIR
sudo cp $HOME/env/Application    $APP_DIR

#Prepare Application to work on the systemd
sudo cp $HOME/env/systemd/board.service $SYSTEMD_PATH
sudo systemctl daemon-reload
sudo systemctl enable board.service
sudo systemctl start board.service

echo "End Process .... OK"

sleep 5
echo "The board will be restart in 5 seconds."

sudo reboot