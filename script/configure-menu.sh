#!/bin/sh

IMG_DIR="/etc/eletrohorse-img/"
APP_DIR="/usr/bin/"
SYSTEMD_PATH="/lib/systemd/system/"

stop_all()
{
    echo "Stop all applications"
    sudo systemctl stop board.service
    sudo pkill python3
}

restart_all()
{
    sudo systemctl start board.service
    sudo reboot
}

image_update()
{
    echo "Update Image."
    if [ ! -d $IMG_DIR ]; then
        sudo mkdir -p $IMG_DIR
    fi
    sudo cp -r $HOME/env/image/*     $IMG_DIR
}

board_program_update()
{
    echo "Updating application board."
    sudo cp $HOME/env/Application    $APP_DIR
}

board_dependency_update()
{
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
}

all_update()
{
    image_update
    board_program_update

    #Prepare display app to auto start after boot
    if [ ! -d $HOME/.config/autostart/ ]; then
        sudo mkdir -p $HOME/.config/autostart/
    fi

    #Prepare Application to work on the systemd
    sudo cp $HOME/env/systemd/board.service $SYSTEMD_PATH
    sudo systemctl daemon-reload
    sudo systemctl enable board.service
    sudo systemctl start board.service

    echo "End Process .... OK"
    sleep 5
    echo "The board will be restart in 5 seconds."
}

while getopts p:u: flag
do
    case "${flag}" in
        p) program=${OPTARG}
           program_selected=true
           ;;
        u) board_update_dep=true
           ;;
    esac
done

if [ "$program" = "board" ]; then
    stop_all
    board_program_update
    restart_all
elif [ "$program" = "all" ]; then
    stop_all
    all_update
    restart_all
else
    echo "Program invalid name."
fi
    
if [ "$board_update_dep" = true ]; then
    board_dependency_update
    restart_all
fi

