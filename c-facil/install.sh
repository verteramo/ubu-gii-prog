#!/bin/bash

path=$(realpath $(dirname $0))
config=$path/../config/*
makefile=$path/main.mk
packages="vim gcc cpp make indent man manpages manpages-dev manpages-es"

sudo apt -qq update
sudo apt -qq upgrade
sudo apt -qq install $packages

for p in $config; do
    ln -vs $p ~/.$(basename $p)
done

if ! grep VERSION_CONTROL ~/.profile > /dev/null; then
    echo "export VERSION_CONTROL=numbered" >> ~/.profile
    source ~/.profile
fi

if ! grep MAKEFILES ~/.profile > /dev/null; then
    echo "export MAKEFILES=$makefile" >> ~/.profile
    source ~/.profile
fi
