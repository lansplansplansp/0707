#include "udp_sock.h"
#include "context.h"
#include "IPMSG.H"
#include "tcp_sock.h"
#include <string.h>
char Filename[BUFFLEN];
int udp_init(int port)
{
    int fd;
    int ret;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == fd){
        printf("ucp socket error\n");
        return -1;
    }

    int on = 1;
    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&on, sizeof(on));
    if(-1 == ret){
        printf("reuse addr error\n");
        return -2;
    }

    struct sockaddr_in addr = {AF_INET};
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(-1 == ret){
        printf("bind error\n");
        return -3;
    }
    // 开启UDP广播功能
    on = 1;
    ret = setsockopt(fd, SOL_SOCKET, SO_BROADCAST,&on, sizeof(on));
    if(-1 == ret){
        printf("broadcast error\n");
        return -4;
    }
    return fd;
}

ipmsg_pkg_t* create_package(int cno, char *msg)
{
    ipmsg_pkg_t *pkg = (ipmsg_pkg_t*)malloc(sizeof(ipmsg_pkg_t));
    //strcpy(pkg->version, );
    sprintf(pkg->version, "%d", IPMSG_VERSION);
    sprintf(pkg->pkt_id, "%d", (int)time(NULL));
    sprintf(pkg->username, "%s", "wendy");
    sprintf(pkg->hostname, "%s", "raspberry");
    sprintf(pkg->msg_type, "%d", cno);
    if(msg != NULL)
        strcpy(pkg->msg_content, msg);
    else
        strcpy(pkg->msg_content, " ");
    return pkg;
}

void free_package(ipmsg_pkg_t **pkg)
{
    free(*pkg);
    *pkg = NULL;
}

void udp_send_message(int fd, struct sockaddr *addr, ipmsg_pkg_t *pkg)
{
    char  buff[MSGLEN] = "";
    sprintf(buff, "%s:%s:%s:%s:%s:%s",
                    pkg->version,
                    pkg->pkt_id,
                    pkg->username,
                    pkg->hostname,
                    pkg->msg_type,
                    pkg->msg_content);
    sendto(fd, buff, strlen(buff), 0, addr, sizeof(*addr));
}

void udp_send_file(int fd, struct sockaddr *addr, ipmsg_pkg_t *pkg, char *filename)
{
    printf("in udp_send_file filename:%s\n",filename);
    char  buff[MSGLEN] = "";
    sprintf(buff, "%s:%s:%s:%s:%s:%s",
                    pkg->version,
                    pkg->pkt_id,
                    pkg->username,
                    pkg->hostname,
                    pkg->msg_type,
                    pkg->msg_content);
    int len = strlen(buff)+1;
    char *attach = buff+len;
    struct stat info;//struct stat这个结构体是用来描述一个linux系统文件系统中的文件属性的结构。
    //第一个参数是文件的路径         //文件序号:文件名:文件大小:最后修改时间:文件属性
    stat(filename, &info);        //头信息长度:文件名:文件大小:文件属性:文件内容（不是）
    sprintf(attach, "%d:%s:%x:%x:%x",0,filename, info.st_size, info.st_ctime, 1);
    printf("in udp_send_file,file size = %d\n",info.st_size);
    len += strlen(attach)+1;
    sendto(fd, buff, len, 0, addr, sizeof(*addr));
}


void login(int ufd)
{
    struct sockaddr_in addr = {AF_INET};
    addr.sin_addr.s_addr = inet_addr("INTADDR_ANY");
    addr.sin_port = htons(IPMSG_PORT);
    // 6291457=0x00600001=0x00200000 | 0x00400000 | 0x00000001
    // 加密信息传输
    ipmsg_pkg_t *pkg = create_package(IPMSG_BR_ENTRY, "login");

    udp_send_message(ufd, (struct sockaddr *)&addr, pkg);

    free_package(&pkg);
}

void logout(int ufd)
{
    struct sockaddr_in addr = {AF_INET};
    addr.sin_addr.s_addr = inet_addr("INTADDR_ANY");
    addr.sin_port = htons(IPMSG_PORT);
    // 6291457=0x00600001=0x00200000 | 0x00400000 | 0x00000001
    // 加密信息传输
    ipmsg_pkg_t *pkg = create_package(IPMSG_BR_EXIT, "logout");
    udp_send_message(ufd, (struct sockaddr *)&addr, pkg);
    free_package(&pkg);
}

void debug_pkg(ipmsg_pkg_t *pkg);
void* udp_send_routine(void* arg)
{		
    context_t *context = (context_t *)arg;
    printf("send udp sockfd = %d\n",context->udp_fd);
    login(context->udp_fd);
    char buff[BUFFLEN];
    while(1)
    {
        fgets(buff, BUFFLEN, stdin);
        if(buff[0] == '\n')
            continue;
        buff[strlen(buff)-1] = '\0';
        if( strncmp(buff, "list", 4) == 0)
        {
            user_list_display(context->listhead);
        }
        else if( strncmp(buff, "talk", 4) == 0)
        {
            printf("in talk:\n");
            fgets(buff, BUFFLEN, stdin);
            buff[strlen(buff)-1] = '\0';
            user_list_t *user;
            user = find_user_byid(context->listhead, atoi(buff));
            struct sockaddr_in addr = {AF_INET};
            addr.sin_port = htons(2425);
            addr.sin_addr.s_addr = inet_addr(user->user_ip);
            fgets(buff, BUFFLEN, stdin);
            ipmsg_pkg_t *pkg =create_package(IPMSG_SENDMSG|IPMSG_SENDCHECKOPT, buff);
            udp_send_message(context->udp_fd, (struct sockaddr *)&addr, pkg);
            free_package(&pkg);
        }
        else if(strncmp(buff, "sendfile", 8) == 0)
        {
            printf("in sendfile:\n");
            fgets(buff, BUFFLEN, stdin);
            buff[strlen(buff)-1] = '\0';
            user_list_t *user;
            user = find_user_byid(context->listhead, atoi(buff));
            struct sockaddr_in addr = {AF_INET};
            addr.sin_port = htons(2425);
            addr.sin_addr.s_addr = inet_addr(user->user_ip);
            fgets(buff, BUFFLEN, stdin);
            buff[strlen(buff)-1] = '\0';
            memmove(Filename,buff,sizeof(buff));
            ipmsg_pkg_t *pkg =
                create_package(IPMSG_SENDMSG|IPMSG_SENDCHECKOPT|IPMSG_FILEATTACHOPT,
                               "send u a file");
            udp_send_file(context->udp_fd, (struct sockaddr *)&addr, pkg, buff);
            printf("in udp send:\n");
            debug_pkg(pkg);
            free_package(&pkg);
        }
    }
    logout(context->udp_fd);
    return NULL;
}

void _ipmsg_split(char *str, char *sp, char *val, int val_len)
{
    char *sub=NULL;
    memset(val, 0, val_len);
    sub = strstr(str, sp);
    if(NULL == sub)
    {
        strncpy(val, str, val_len);
    }
    else
    {
        strncpy(val, str, MIN(sub-str, val_len));
    }
}
void file_name(char *buff, char *File,char *p)
{
    _ipmsg_split(buff, ":", File, BUFFLEN);
    buff+= 1+strlen(File);
    _ipmsg_split(buff, ":", File, BUFFLEN);
    buff+= 1+strlen(File);
    _ipmsg_split(buff, ":", p, 4);
    printf("p:%s\n",p);
}
void ipmsg_split(char *buff, ipmsg_pkg_t *pkg)
{
    _ipmsg_split(buff, ":", pkg->version, BUFFLEN);
    buff+= 1+strlen(pkg->version);

    _ipmsg_split(buff, ":", pkg->pkt_id, BUFFLEN);
    buff+= 1+strlen(pkg->pkt_id);

    _ipmsg_split(buff, ":", pkg->username, BUFFLEN);
    buff+= 1+strlen(pkg->username);

    _ipmsg_split(buff, ":", pkg->hostname, BUFFLEN);
    buff+= 1+strlen(pkg->hostname);

    _ipmsg_split(buff, ":", pkg->msg_type, BUFFLEN);
    buff+= 1+strlen(pkg->msg_type);

    _ipmsg_split(buff, ":", pkg->msg_content, MSGLEN);
}

void debug_pkg(ipmsg_pkg_t *pkg)
{
    char buff[MSGLEN];
    sprintf(buff, "%s:%s:%s:%s:%s:%s",
                    pkg->version,
                    pkg->pkt_id,
                    pkg->username,
                    pkg->hostname,
                    pkg->msg_type,
                    pkg->msg_content);
    printf("%s\n", buff);
}

void *udp_recv_routine(void *arg)
{
    context_t *context = (context_t *)arg;
    printf("recv udp sockfd = %d\n", context->udp_fd);
    char buff[MSGLEN];
    int cnt;
    struct sockaddr_in peer;
    socklen_t peerlen;
    ipmsg_pkg_t  mpkg;
    while(1)
    {
        peerlen = sizeof(peer);
        cnt = recvfrom(context->udp_fd, buff, MSGLEN, 0,
                       (struct sockaddr*)&peer, &peerlen);
        printf("got msg size %d:\n", cnt);
        if(cnt<=0)
            continue;
        ipmsg_split(buff, &mpkg);
        printf("in udp recv:\n");
        debug_pkg(&mpkg);

        switch(GET_MODE(atoi(mpkg.msg_type)))
        {
            case IPMSG_BR_ENTRY :
                    printf("someone bc entry\n");
                    add_user(context->listhead, mpkg.username,
                             mpkg.hostname, inet_ntoa(peer.sin_addr));
                    ipmsg_pkg_t *pkg = create_package(IPMSG_ANSENTRY, "wendy");
                    udp_send_message(context->udp_fd, (struct sockaddr *)&peer, pkg);
                    free_package(&pkg);
                    break;
            case IPMSG_BR_EXIT:
                    printf("someone exit\n");
                    del_user(context->listhead, inet_ntoa(peer.sin_addr));
                    break;
            case IPMSG_ANSENTRY:
                    printf("anser entry\n");
                    add_user(context->listhead, mpkg.username,
                             mpkg.hostname, inet_ntoa(peer.sin_addr));
                    break;
            case IPMSG_SENDMSG:
                    printf("the send hui:%s\n", mpkg.msg_content);
                                                    //传送检查(需要对方返回确认信息)
                    if(GET_OPT(atoi(mpkg.msg_type)) & IPMSG_SENDCHECKOPT)
                    {
                        printf("in send MSG:\n");
                        ipmsg_pkg_t *pkg = create_package(IPMSG_RECVMSG, mpkg.pkt_id);
                        udp_send_message(context->udp_fd, (struct sockaddr *)&peer, pkg);
                        free_package(&pkg);
                    }
                    if(GET_OPT(atoi(mpkg.msg_type)) & IPMSG_FILEATTACHOPT)//传送文件选项
                    {
                        printf("in send file\n");
                        char *fileinfo = buff + strlen(buff)+1;//+1是跳过\0
                        printf("file info : %s\n", fileinfo);

                        //how to save file
                        char filelen[BUFFLEN];
                        file_name(fileinfo,Filename,filelen);
                        printf("recvfile:%s\n",Filename);
                        int a = atoi(filelen);
                        printf("filelen:%d\n",a);
                        char sfile[BUFFLEN];
                        sprintf(sfile,"%x:%x:%d",mpkg.pkt_id,0,0);
                        ipmsg_pkg_t *pkg = create_package(96,sfile);
                        udp_send_message(context->udp_fd, (struct sockaddr *)&peer, pkg);
                        free_package(&pkg);
                        printf("please\n");
                    }
            break;
        }
    }
    return (void *)0;
}


