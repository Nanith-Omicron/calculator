#!/bin/bash
echo "Building Calculator"
cd ./build
cmake ..
make -j$(nproc)
sleep .5

