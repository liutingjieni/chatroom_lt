/*************************************************************************
	> File Name: dfi.h
	> Author: 
	> Mail: 
	> Created Time: 2019年08月12日 星期一 17时36分59秒
 ************************************************************************/
#include <time.h>

#define EXIT       0
#define LOGIN      1
#define REGIST     2
#define REPASSWD   3
#define ADD_FRIEND 4
#define LIST_FRI   5
#define ONLINE_FRI 6
#define CHAT_FRI   7
#define STORE_CHAT 8
#define DELE_FRI   9
#define CREAT_GROUP 10
#define JOIN_GROUP  11
#define QUIT_GROUP  12
#define DELE_GROUP  13
#define GROUP_MES   14
#define CHAT_GROUP  15
#define STORE_G     16
#define SET_UP      17
#define SEND_FILE   18
#define OK_FILE     19
#define JOIN_USER   20
#define DELE_USER   21

typedef struct package {
    int  type;
    int  account;
    char send_name[100];
    int  send_account;
    time_t time;
    char mes[1000];
    char mes2[1000];
} PACK;

typedef struct friends {  //好友列表
    int  account[50];
    char name[50][100];
    int online[50];
    int  len;
}fri;

typedef struct store_chat { //私聊记录
    int account[100];
    int send_account[100];
    char mes[100][1000];
    int len;
}STR;

typedef struct group {  //群信息
    int account[50];
    char name[50][100];
    int online[50];
    int cli_fd[50];
    int flag[50];
    int len;
}GROUP;

typedef struct store_group {
    int usr_account[100];
    char use_name[100][100];
    char mes[100][1000];
    int len;
}STR_G;
