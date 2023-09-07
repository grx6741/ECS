#!/bin/sh

set -xe

clear
cd build
meson compile
cd ..
./build/main
