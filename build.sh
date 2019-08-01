#!/usr/bin/env bash

[ ! -d "./build" ] && mkdir build

cd ./build

cmake ../src -DCMAKE_INSTALL_PREFIX=../install && \
make -j$(grep -c ^processor /proc/cpuinfo) && \
make install && \
echo "Built and Installed Successfully!"
