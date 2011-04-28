#include <linux/unistd.h> 
#include <sys/syscall.h> 
#include <stdio.h>

#define __NR_get_slob_amt_claimed 338
#define __NR_get_slob_amt_free 339

int main() 
{ 
    printf("running syscalls\n");
    syscall( __NR_get_slob_amt_claimed );
    syscall( __NR_get_slob_amt_free );
    printf("done running syscalls\n");
    return 0; 
}
