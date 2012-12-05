#! /bin/bash
#  
#    Swift Fox Compiler
#    Copyright (C) 2009-2012 Marcin Szczodrak
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

