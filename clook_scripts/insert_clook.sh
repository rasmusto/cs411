#!/bin/bash

echo '8 1 4 7' > /proc/sys/kernel/printk

echo "Switching to noop"
echo noop > /sys/block/sdb/queue/scheduler
cat /sys/block/sdb/queue/scheduler
echo

echo "Removing old module"
modprobe -r clook-iosched
cat /sys/block/sdb/queue/scheduler
echo

echo "Adding clook module:"
modprobe clook-iosched
cat /sys/block/sdb/queue/scheduler
echo

echo "Activating clook module:"
echo clook > /sys/block/sdb/queue/scheduler
cat /sys/block/sdb/queue/scheduler
echo
