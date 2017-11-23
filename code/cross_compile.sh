#!/bin/bash

# download toolchain
VERSION=gcc-linaro-6.4.1-2017.08-x86_64_arm-linux-gnueabihf
if [ ! -d "$VERSION" ]; then
	wget -c https://releases.linaro.org/components/toolchain/binaries/6.4-2017.08/arm-linux-gnueabihf/$VERSION.tar.xz
	echo "extracting cross-compiler toolchain..."
	tar xf $VERSION.tar.xz
	rm -f $VERSION.tar.xz
fi

# set environment variables and make
export TOOLCHAIN=`pwd`/$VERSION/bin/arm-linux-gnueabihf-

make