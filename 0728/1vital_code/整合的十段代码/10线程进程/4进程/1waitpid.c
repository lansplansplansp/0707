#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()

{
    int i=0;
    pid_t pid, pr;
    pid=fork();

    if(pid<0)
        printf("Error occured on forking.\n");
    else if(pid==0){
        sleep(10);
        exit(0);
    }
    do{
        //pr=waitpid(pid, NULL, 0);//死等子进程
        pr=waitpid(pid, NULL, WNOHANG); /* 使用了WNOHANG参数，waitpid不会在这里等待 */
        //pr=waitpid(-1, NULL, WNOHANG);//等价
        if(pr==0){ /* 如果没有收集到子进程 */
            printf("%dNo child exited\n",++i);
            sleep(1);
        }
    }while(pr==0); /* 没有收集到子进程，就回去继续尝试 */
    if(pr==pid)
        printf("successfully get child %d and father is %d\n", pr,getpid());
    else
        printf("some error occured\n");
    return 0;
}
