#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <wiringPi.h>

//gcc webLed.c -lwiringPi
//http://172.27.35.2:4321/ledoff.act

const static char http_head_error[] = "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n";
const static char http_head_ok[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
//LED关灯页面
const static char http_body_off[] =
"<html><head><title>RPI_led</title></head>"
"<body><h1>LED 7 is off</h1>"
"<div/><input type='button' value=led_ON onclick=\"location.href='ledon.act';\" />"
"<p><input type='button' value=led_OFF onclick=\"location.href='ledoff.act';\" />"
"</body></html>";
//LED开灯页面
const static char http_body_on[] =
"<html><head><title>RPI_led</title></head>"
"<body><h1>LED 7 is on</h1>"
"<div/><input type='button' value=led_ON onclick=\"location.href='ledon.act';\" />"
"<p><input type='button' value=led_OFF onclick=\"location.href='ledoff.act';\" />"
"</body></html>";
int tcp_serv_init(int serv_port)
{
    int port = serv_port;
    int servfd;
    servfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in  servaddr;
    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.s_addr = 	htonl(INADDR_ANY);
    servaddr.sin_port =  htons(port);
    int ret;
    ret = bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(ret < 0 )
    {
        printf("bind error\n");
        exit(1);
    }
    listen(servfd, 5);
    return servfd;
}

void led_init()
{
    pinMode(8, OUTPUT); //D0
    pinMode(9, OUTPUT);	//R
    pinMode(7, OUTPUT);	//G
    pinMode(0, OUTPUT);	//B

    digitalWrite(9, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(0, HIGH);
}
void  http_send_file(int sockfd, char *filename)
{
    if(strcmp(filename, "/ledoff.act")==0)
    {
        write(sockfd, http_head_ok, strlen(http_head_ok));
        write(sockfd, http_body_off, strlen(http_body_off));
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
    }
    else if(strcmp(filename, "/ledon.act") == 0)
    {
        write(sockfd, http_head_ok, strlen(http_head_ok));
        write(sockfd, http_body_on, strlen(http_body_on));
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
    }
    else
    {
        write(sockfd, http_head_error, strlen(http_head_error));
    }
}
void serve(int sockfd)
{
    char buff[1024];
    int cnt;
    cnt = read(sockfd, buff, 1024);
    printf("cnt=%d\n", cnt);
    write(1,buff,cnt);
    if(strncmp(buff, "GET", 3) == 0)
    {
        char *file = buff + 4;
        char *space = strchr(file, ' ');
        *space = '\0';
        http_send_file(sockfd, file);
    }
}
int main()
{
    int fd = tcp_serv_init(4321);
    // 硬件初始化
    wiringPiSetup();
    // LED初始化
    led_init();
    int newfd;
    while(1)
    {
        printf("waitng for client .......\n");
        newfd = accept(fd, NULL, NULL);
        printf("client connect successful\n");
        serve(newfd);
        close(newfd);
    }
    close(fd);
    return 0;
}
