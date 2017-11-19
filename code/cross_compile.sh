#!/bin/bash

VERSION=gcc-linaro-7.1.1-2017.08-x86_64_arm-linux-gnueabihf
if [ ! -d "$VERSION" ]; then
	wget -c https://releases.linaro.org/components/toolchain/binaries/latest/arm-linux-gnueabihf/$VERSION.tar.xz
	echo "extracting cross-compiler toolchain..."
	tar xf $VERSION.tar.xz
	rm -f $VERSION.tar.xz
fi

export TOOLCHAIN=`pwd`/gcc-linaro-7.1.1-2017.08-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

make