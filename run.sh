#!/bin/bash

if [ `whoami` != "root" ];
then
    echo "run again as root"
    exit
fi

if [ -f linux-2.6.34.7/drivers/block/osurd.ko ]
then
    insmod linux-2.6.34.7/drivers/block/osurd.ko
else
    cd linux-2.6.34.7
    make modules
    cd ..
fi
