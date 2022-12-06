#!/bin/bash
clear
echo "Building Calculator"
cd ./build
cmake ..
make -j$(nproc)
sleep 2

