#!/bin/bash

#Create diff of kernel with clean copy
git diff 08ccd linux-2.6.34.7 > ./2.6.34.7-my_syscall-team08.patch

#Create git log file
git log > git.log

tar cvf proj01.tar.gz /boot/vmlinuz-my_syscall-team08
tar rvf proj01.tar.gz proj01-iosched
tar rvf proj01.tar.gz proj01-syscall
tar rvf proj01.tar.gz 2.6.34.7-my_syscall-team08.patch
tar rvf proj01.tar.gz git.log

#Clean up files
rm 2.6.34.7-my_syscall-team08.patch
rm git.log
