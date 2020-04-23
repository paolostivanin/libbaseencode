#!/bin/bash

set -e

mkdir build && cd $_
cmake .. -DCMAKE_INSTALL_PREFIX=/usr 
make -j2
make install
cmake .. -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_TESTING=ON
make -j2
./tests/test_all
