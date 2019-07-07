#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
    int status;
    pid_t pid,pr;
    pid=fork();
    if(pid<0)
        printf("error ocurred!\n");
    else if(pid==0){
        printf("This is child process with pid of %d.\n",getpid());
        exit(3); /* 子进程返回3 */
    }
    else{
    pr=wait(&status);
    if(WIFEXITED(status)){
        printf("the child process %d exit normally.\n",pr);
        printf("the return code is %d.\n",WEXITSTATUS(status));
    }else
    printf("the child process %d exit abnormally.\n",pr);
    }
}
