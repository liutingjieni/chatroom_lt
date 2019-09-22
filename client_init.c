/*************************************************************************
	> File Name: client_init.c
	> Author: 
	> Mail: 
	> Created Time: 2019年08月07日 星期三 14时31分44秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define IP "192.168.3.5"

#define PORT 8888 

int init()
{
    int cli_fd;
    struct sockaddr_in serv_addr;
    
    cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    
    if(connect(cli_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
    {
        perror("connect 出现问题");
        exit(-1);
    }
    printf("客户端启动成功");
    return cli_fd;
}
