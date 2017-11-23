#!/bin/bash

VERSION=gcc-linaro-6.4.1-2017.08-x86_64_arm-linux-gnueabihf
export TOOLCHAIN=`pwd`/../$VERSION/bin/arm-linux-gnueabihf-

make
