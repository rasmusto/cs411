#include <linux/unistd.h> 
#include <sys/syscall.h> 
#include <stdio.h>
#include <unistd.h>

#define __NR_get_slob_amt_claimed 338
#define __NR_get_slob_amt_free 339

int main() 
{ 
    printf("Checking current memory usage...\n");
    syscall( __NR_get_slob_amt_claimed );
    syscall( __NR_get_slob_amt_free );
    printf("Done checking current memory usage!\n");

    printf("Running command...\n");
    system("cat /proc/cpuinfo| grep [0-9] | sort | tr cpu ppu");
    printf("Done running command!\n");

    printf("Checking new memory usage...\n");
    syscall( __NR_get_slob_amt_claimed );
    syscall( __NR_get_slob_amt_free );
    printf("Done checking new memory usage!\n");

    system("dmesg | tail --lines=4");

    return 0; 
}
