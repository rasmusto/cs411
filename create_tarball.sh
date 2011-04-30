#!/bin/bash

#Create diff of kernel with clean copy
git diff 08ccd linux-2.6.34.7 > ./2.6.34.7-proj02.patch

#Create git log file
git log > git.log

tar cvf proj02.tar.gz /boot/vmlinuz-2.6.34-7-proj02
tar rvf proj02.tar.gz slob_syscalls
tar rvf proj02.tar.gz 2.6.34.7-proj02.patch
tar rvf proj02.tar.gz git.log

#Clean up files
rm 2.6.34.7-proj02.patch
rm git.log
