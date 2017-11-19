#!/bin/bash

#tar -czf code.tar.gz code
#scp code.tar.gz debian@beaglebone.local:/home/debian/solver
#rm code.tar.gz
#ssh debian@beaglebone.local "rm -r /home/debian/solver/code; tar -xzf /home/debian/solver/code.tar.gz -C /home/debian/solver; rm /home/debian/solver/code.tar.gz; exit;"

cd code
./cross_compile.sh
scp bin/rbs1 debian@beaglebone.local:/home/debian/solver