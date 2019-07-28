#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
//不能改成.cpp文件，否则write、close就会未声明报错
//gcc webLed.c 
//http://172.27.35.2:4321/ledoff.act(172.27.35.2:运行代码的设备IP)

char httpApi_response_formate_PicData[] = 
{
	"HTTP/1.1 200 OK\r\n"
	"Connection: Close\r\n"
	"Content-Type: image/jpeg;\r\n"
	"Content-Length: %d\r\n\r\n"
};

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

void  http_send_file(int sockfd, char *filename)
{
    if(strcmp(filename, "/ledoff.act")==0)
    {
        write(sockfd, http_head_ok, strlen(http_head_ok));
        write(sockfd, http_body_off, strlen(http_body_off));

    }
    else if(strcmp(filename, "/ledon.act") == 0)
    {
        write(sockfd, http_head_ok, strlen(http_head_ok));
        write(sockfd, http_body_on, strlen(http_body_on));

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
    cnt = read(sockfd, buff, 1024);//接收HTTP请求头:
    printf("cnt=%d\n", cnt);
    write(1,buff,cnt);
	//GET /ledon.act HTTP/1.1
	//Host: 128.128.255.129:4321
	//Connection: keep-alive
	//Upgrade-Insecure-Requests: 1
	//User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36
	//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	//Referer: http://128.128.255.129:4321/ledoff.act
	
	//第二种请求情况（有历史记录）
	//GET /ledoff.act HTTP/1.1
	//Host: 128.128.255.129:4321
	//Connection: keep-alive
	//Upgrade-Insecure-Requests: 1
	//User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36
	//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
	//Accept-Encoding: gzip, deflate
	//Accept-Language: zh-CN,zh;q=0.9
	//Cookie: __guid=217408534.4327671638140259300.1561512834310.0479; monitor_count=1

	//{//HTTP请求头格式
	//	"POST %s HTTP/1.1\r\n"//路径
	//	"Content-Type: application/json;charset=UTF-8\r\n"
	//	"User-Agent: Mozilla/4.0\r\nCache-Control: no-cache\r\nAccept: */*\r\n"
	//	"Host: %s:%d\r\n"//或域名:port
	//	"Content-Length: %d\r\n"//JSON包长度
	//	"Connection: Close\r\n\r\n"
	//	"%s"//JSON包
	//};
	//{//HTTP回应头格式
	//	"HTTP/1.1 200 OK\r\n"
	//	"Connection: Close\r\n"
	//	"Content-Type: application/json;charset=UTF-8\r\n"
	//	"Content-Length: %d\r\n\r\n"
	//	"%s"
	//};
    if(strncmp(buff, "GET", 3) == 0)
    {
        char *file = buff + 4;
        char *space = strchr(file, ' ');
        *space = '\0';//丢掉file的后续字符串
        http_send_file(sockfd, file);
    }
}
int main()
{
    int fd = tcp_serv_init(4321);//sfd

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
