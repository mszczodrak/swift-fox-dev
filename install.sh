#! /bin/bash
# Marcin Szczodrak

ORG_DIR=`pwd`

if [ -n "${FENNEC_FOX_LIB+1}" ]; then
    echo FENNEC_FOX_LIB is set to $FENNEC_FOX_LIB
else
    echo FENNEC_FOX_LIB is unset
    exit
fi

cd ./src/sf

echo compiling
make clean
make
echo sfc and fennec are ready to be installed
sudo make install

echo clean compilation temp files
make clean

cd $ORG_DIR

