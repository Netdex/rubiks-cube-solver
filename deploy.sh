tar -czf code.tar.gz code
scp code.tar.gz debian@beaglebone.local:/home/debian/solver
rm code.tar.gz
