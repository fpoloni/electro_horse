#!/bin/bash

BASE_DIR="/home/fpsantos/devel/eletrohorse-top/"
## init
## look for empty dir 
if [ -d $BASE_DIR ]; then
    rm -rf $BASE_DIR/env/
fi

mkdir -p $BASE_DIR/env/display/
mkdir -p $BASE_DIR/env/image/
mkdir -p $BASE_DIR/env/systemd/

cp     $BASE_DIR/build/eletro-app/Application     $BASE_DIR/env/
rm -rf $BASE_DIR/eletro-display/repo/python/gui/__pycache__/
cp -r  $BASE_DIR/eletro-display/repo/python/gui/* $BASE_DIR/env/display/
cp -r  $HOME/Downloads/content_screen/*  $BASE_DIR/env/image/

cp $BASE_DIR/script/systemd/board.service   $BASE_DIR/env/systemd/
cp $BASE_DIR/script/systemd/display.desktop $BASE_DIR/env/systemd/
cp $BASE_DIR/script/config.txt $BASE_DIR/env/


cp  $BASE_DIR/script/configure.sh           $BASE_DIR/env/

#script in test
cp  $BASE_DIR/script/configure-menu.sh       $BASE_DIR/env/

tree -L 2 $BASE_DIR/env/

echo "If you do you able to see the directory files above, the copy happened as well"
