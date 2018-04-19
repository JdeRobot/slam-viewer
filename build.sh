#!/bin/bash

echo "Configuring and building SLAM Viewer ..."

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
