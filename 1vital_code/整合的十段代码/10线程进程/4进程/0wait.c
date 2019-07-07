#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()

{
    pid_t pc,pr;
    pc=fork();
    if(pc<0)
        printf("create process error\n");
    else if(pc==0){
        printf("This is child process with pid of %d\n",getpid());
        sleep(5);
    }
    else{
        pr=wait(NULL);
        printf("I catched a child process with pid of %d and father is %d\n",pr,getpid());
    }
    exit(0);
}

