#!/bin/bash

ROOT=../
TAR_GZ=$ROOT/src
PKG=$ROOT/ubuntu_package
BASE_NAME=sfc
VERSION=0.79

#rm -rf $BASE_NAME*
#cd $TAR_GZ
#./Bootstrap
#cd $PKG
cp $TAR_GZ/$BASE_NAME-$VERSION.tar.gz ./$BASE_NAME\_$VERSION.orig.tar.gz
tar zxvf $BASE_NAME\_$VERSION.orig.tar.gz
cd $BASE_NAME\_$VERSION
dh_make -e marcin@ieee.org


