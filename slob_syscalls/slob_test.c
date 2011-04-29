#include <linux/unistd.h> 
#include <sys/syscall.h> 
#include <stdio.h>
#include <unistd.h>

#define __NR_get_slob_amt_claimed 338
#define __NR_get_slob_amt_free 339

int main() 
{ 
    printf("\n");
    printf("Checking current memory usage... ");
    syscall( __NR_get_slob_amt_claimed );
    syscall( __NR_get_slob_amt_free );
    printf("Done!\n");
    printf("\n");
    system("dmesg | tail --lines=2");
    printf("\n");

    printf("Running command... ");
    system("cat /proc/cpuinfo| grep [0-9] | sort | tr cpu ppu >> /dev/null");
    printf("Done!\n");
    printf("\n");

    printf("Checking new memory usage... ");
    syscall( __NR_get_slob_amt_claimed );
    syscall( __NR_get_slob_amt_free );
    printf("Done!\n");
    printf("\n");
    system("dmesg | tail --lines=2");
    printf("\n");

    return 0; 
}
