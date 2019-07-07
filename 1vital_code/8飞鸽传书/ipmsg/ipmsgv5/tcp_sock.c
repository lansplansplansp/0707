#include "tcp_sock.h"
#include "context.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int  tcp_init(int port)
{
    int fd;
    int ret;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == fd){
    perror("tcp socket\n");
        return -1;
    }

    int on = 1;
    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&on, sizeof(on));
    if(-1 == ret){
    perror("reuse addr\n");
        return -2;
    }
    struct sockaddr_in addr = {AF_INET};
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(-1 == ret){
    perror("bind\n");
        return -3;
    }

    listen(fd, 5);

    return fd;

}

void *tcp_send_routine(void* arg)
{
    context_t *context = (context_t *)arg;
    printf("send tcp sockfd = %d\n",context->tcp_fd);
    int newfd;
    char buff[BUFFLEN];
    int cnt;
    struct sockaddr_in peer;
    socklen_t len ;
    ipmsg_pkg_t  mpkg;
    while(1)
    {
        len =  sizeof(peer);
        newfd = accept(context->tcp_fd, (struct sockaddr*)&peer, &len);
        printf("tcp send ip:%s connect\n", inet_ntoa(peer.sin_addr));
        cnt = read(newfd, buff, BUFFLEN);
        write(1, buff, cnt);
        printf("\n");
        ipmsg_split(buff, &mpkg);
        switch(GET_MODE(atoi(mpkg.msg_type)))
        {
            case IPMSG_GETFILEDATA:
                printf("in tcp send file:\n");
                char  filebuff[1024] = "";
                int filefd = open(Filename,O_RDONLY);
                while(1)
                {
                    int cnt = read(filefd,filebuff,1024);
                    if(cnt == 0)break;
                }
                close(filefd);
                send(newfd,filebuff,strlen(filebuff),0);
            //break;
        }
        printf("file ok\n");
    }
    close(newfd);
}

void *tcp_recv_routine(void *arg)
{
    context_t *context = (context_t *)arg;
    printf("recv tcp sockfd = %d\n", context->tcp_fd);
    int newfd;
    char buff[MSGLEN];
    int cnt;
    struct sockaddr_in peer;
    socklen_t peerlen;
    ipmsg_pkg_t  mpkg;
    int filefd = open(Filename,O_WRONLY|O_CREAT);
    while(1)
    {
        peerlen =  sizeof(peer);
        newfd = accept(context->tcp_fd, (struct sockaddr*)&peer, &peerlen);
        printf("tcp recv ip:%s connect\n", inet_ntoa(peer.sin_addr));

        cnt = read(newfd, buff, BUFFLEN);
        write(1, buff, cnt);
        printf("\n");

        ipmsg_split(buff, &mpkg);
        printf("1id:%x\n",mpkg.pkt_id);
        printf("2id:%d\n",mpkg.pkt_id);
        printf("msg:%s\n",mpkg.msg_content);
        switch(GET_MODE(atoi(mpkg.msg_type)))
        {
            case IPMSG_GETDIRFILES:
                printf("in tcp recv file:\n");
                cnt = write(newfd, buff, MSGLEN);
                read(filefd, buff, BUFFLEN);
                printf("\n");
        }
    }
    close(newfd);
    close(filefd);
    return (void *)0;
}
