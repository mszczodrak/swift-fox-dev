#!/bin/bash
# Marcin Szczodrak

DEV_REPO=./
PUB_REPO=../swift-fox
MAIN_FOLDER=src
PUBS=pubs

echo "Clean Repo"
make maintainer-clean

echo "Delete all files from $PUB_REPO"
rm -rf $PUB_REPO/*

while read -r path
do
	echo "Copying - $path"
	cp -R  --parents $path $PUB_REPO
done < "$PUBS"

cd $PUB_REPO
git add *
git commit -am "Sync from `date`"

