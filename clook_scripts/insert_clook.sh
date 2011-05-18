#!/bin/bash

echo '8 1 4 7' > /proc/sys/kernel/printk
echo "Status:"
cat /sys/block/sdb/queue/scheduler
echo clook > /sys/block/sdb/queue/scheduler
echo "Status:"
cat /sys/block/sdb/queue/scheduler
