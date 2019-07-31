#!/usr/bin/env bash

[ ! -d "./build" ] && mkdir build

cd ./build

cmake ../src -DCMAKE_INSTALL_PREFIX=../install && \
make -j8 && \
make install && \
echo "Built and Installed Successfully!"
