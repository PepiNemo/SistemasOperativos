#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>//nmap para compartir memoria

void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, 0, 0);
}


int main(int argc, char *argv[]){
    pid_t me, childpid;
    void* shareMem = create_shared_memory(124);
    childpid=fork();
    if(childpid==0){
        printf("El hijo cambia la posicion \n");
        int num2=33;
        int* posicion2=&num2;
        memcpy(shareMem, posicion2, sizeof(posicion2));
    }
    if(childpid >0){
        int* num1;
        num1=shareMem; 
        sleep(1);
        printf("El padre le por segunda vez : %d \n", *num1);
    }

    return 0;
}
//https://ajaxhispano.com/ask/como-usar-la-memoria-compartida-con-linux-en-c-28210/