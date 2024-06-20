#!/bin/bash

path=$(realpath $(dirname $0))
config=$path/config/*
packages="vim gcc cpp make indent man manpages manpages-dev manpages-es"

sudo apt -qq remove $packages

for file in $config; do
    rm -f ~/.$(basename $file)
done

sed -i "/export MAKEFILES/d" ~/.profile
sed -i "/export VERSION_CONTROL/d" ~/.profile

unset MAKEFILES
unset VERSION_CONTROL
