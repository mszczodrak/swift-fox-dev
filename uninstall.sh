#! /bin/bash

ORG_DIR=`pwd`

if [ -n "${FENNEC_FOX_LIB+1}" ]; then
    echo FENNEC_FOX_LIB is set to $FENNEC_FOX_LIB
else
    echo FENNEC_FOX_LIB is unset
fi

cd ./src/sf

echo "cleaning source code"
make clean

echo sfc and fennec are ready to be installed
sudo make uninstall

cd $ORG_DIR

