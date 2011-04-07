#include <linux/unistd.h> 
#include <sys/syscall.h> 
#define __NR_team08 338 
int main() 
{ 
    syscall( __NR_team08 ); 
    return 0; 
}
