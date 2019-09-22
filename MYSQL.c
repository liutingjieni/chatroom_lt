/*************************************************************************
	> File Name: mysql.c
	> Author: 
	> Mail: 
	> Created Time: 2019年08月07日 星期三 09时02分57秒
 ************************************************************************/

#include "dfi.h"
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>


MYSQL mysql;
MYSQL_RES  *result=NULL;
MYSQL_ROW  row;
MYSQL_FIELD *field;


void MYSQL_init()
{
    if (NULL == mysql_init(&mysql)) {
        perror("mysql_init");
    }
    mysql_real_connect(&mysql, "127.0.0.1", "root", "200713", "chatroom", 0, NULL, 0);
    if (mysql_set_character_set(&mysql, "utf8")<0){
        perror("mysql_set_character");
    }
}

void MYSQL_main_init()
{
    MYSQL_init();
    char buff[1000];
    sprintf(buff, "update user set online = 0");
    if (mysql_query(&mysql,buff))
    {
        perror("main init :mysql_query");
    }

    mysql_close(&mysql);
}


int MYSQL_login(int account, char *password, int cli_fd)
{
    int ret;
    int flag = 1;
    char buff[1000];
    sprintf(buff, "select *from user where id = %d ", account);//连接两个字符串
    ret = mysql_query(&mysql,buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("login:mysql_store_result");
        }
        //num_fields=mysql_num_fields(result);    

        while (row=mysql_fetch_row(result)) { 
            if (strcmp(password, row[2]) == 0) {
                printf("客户端%d 登录成功\n",account);
            
                sprintf(buff,"update user set online = 1 ,sock_fd = %d where id = %d",cli_fd, account);
                if (mysql_query(&mysql, buff)) {
                    perror("login:mysql_query");
                }
                mysql_free_result(result);
                mysql_close(&mysql);
                return 0;
            }
        }
    }
    return -1;
}
int MYSQL_regist(char *mes, char *mes2)
{
    int ret;
    int num_fields;

    char buff[1000];
    sprintf(buff, "insert into user (name,passwd)values (\"%s\",\"%s\")", mes,mes2);//连接两个字符串
    ret = mysql_query(&mysql,buff);

    if (!ret) {
        sprintf(buff, "select LAST_INSERT_ID()");//连接两个字符串
        ret = mysql_query(&mysql,buff);
        if (!ret) {
            result = mysql_store_result(&mysql);    //返回查询结果
            if (!result) {
                perror("login:mysql_store_result");
            }
            while (row=mysql_fetch_row(result)) {
                int id = atoi(row[0]);
                printf("客户端 %d 注册成功\n",id);
                mysql_close(&mysql);
                return id;
            }
        }
    }
    else {
        mysql_close(&mysql);
        return -1;
     }
}

int MYSQL_repass(int account,char *old_passwd, char *new_passwd)
{
    int ret;

    char buff[1000];
    sprintf(buff, "select *from user where id = %d ", account);//连接两个字符串
    ret = mysql_query(&mysql,buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("login:mysql_store_result");
        }
        //num_fields=mysql_num_fields(result);    

        while (row=mysql_fetch_row(result)) { 
            if (strcmp(old_passwd, row[2]) == 0) {
            
                sprintf(buff,"update user set passwd = '%s' where id = %d",new_passwd , account);
                if(mysql_query(&mysql, buff)) {
                    perror("login:mysql_query");
                }

                printf("客户端%d 修改密码成功\n",account);
                mysql_free_result(result);
                mysql_close(&mysql);
                return 0;
            }
        }
    }
    return -1;
}

int MYSQL_exit(int account)
{
    char buff[1000];
    int flag = 0;
    sprintf(buff,"update user set online = %d  where id = %d",flag,account);
    mysql_query(&mysql, buff);    
}

int MYSQL_find_frirela(int id1, int id2)
{
    MYSQL_init();
    int ret;
    char buff[1000];
    int i = 0;

    sprintf(buff,"select * from friends where id1 = %d and id2 = %d", id1,id2);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        while (row=mysql_fetch_row(result)) {
            mysql_free_result(result);
            mysql_close(&mysql);
            return 0;
        }
    }
    mysql_free_result(result);
    mysql_close(&mysql);
    return -1;
}

fri MYSQL_find_fd(int account)
{
    MYSQL_init();
    int ret; 
    char buff[1000];
    fri f;
    sprintf(buff,"select * from user where id = %d",account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("addfriend:mysql_store_result");
        }
        if (row=mysql_fetch_row(result)) {
            f.account[0] = atoi(row[4]);  //套接字
            f.online[0] = atoi(row[3]);
            strcpy(f.name[0], row[1]);
        }
        else {
            f.account[0] = -1;
        }
    }
        mysql_free_result(result);
        mysql_close(&mysql);
        return f;
}
int  MYSQL_find_fd_user(int account)
{
    MYSQL_init();
    int ret; 
    char buff[1000];
    int f;
    sprintf(buff,"select * from user where id = %d",account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("addfriend:mysql_store_result");
        }
        if (row=mysql_fetch_row(result)) {
            f = atoi(row[4]);    
        }
    }
        mysql_free_result(result);
        mysql_close(&mysql);
        return f;
}

int MYSQL_addfriend_store(int account, int send_account)
{
    MYSQL_init();
    int ret;
    char buff[1000];
    sprintf(buff, "insert into friends (id1,id2)values (%d,%d)", account,send_account);//连接两个字符串
    ret = mysql_query(&mysql,buff);
    if (!ret) {
        sprintf(buff, "insert into friends (id1,id2)values (%d,%d)", send_account,account);//连接两个字符串
        ret = mysql_query(&mysql,buff);
        if (!ret) {
            mysql_close(&mysql);
            return 0;
        }
        else {
            mysql_close(&mysql);
             return -1;
        }
    }
    else {
        mysql_close(&mysql);
        return -1;
     }
}

fri MYSQL_list_fri(int account)
{
    MYSQL_init();
    int ret; 
    int send_cli_fd;
    char buff[1000];
    fri p;
    int i = 0;

    sprintf(buff,"select * from friends where id1 = %d",account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        while (row=mysql_fetch_row(result)) {
            p.account[i] = atoi(row[1]);
            i++;
        }
    }
    p.len = i;
    p.account[p.len] = -1;
    for(i = 0; i < p.len; i++)
    {
        sprintf(buff,"select * from user where id = %d",p.account[i]);
        ret = mysql_query(&mysql, buff);
        if (!ret) {
            result = mysql_store_result(&mysql);    //返回查询结果
            if (!result) {
                perror("list_friend:mysql_store_result");
            }
            while (row=mysql_fetch_row(result)) {
                strcpy(p.name[i] , row[1]);
            }
        }
    }
    mysql_close(&mysql);
    return p;
}

fri MYSQL_online_fri(int account)
{
    MYSQL_init();
    int ret;
    int send_cli_fd;
    char buff[1000];
    fri p;
    int i = 0;

    sprintf(buff,"select * from friends where id1 = %d",account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        while (row=mysql_fetch_row(result)) {
            p.account[i] = atoi(row[1]);
            i++;
        }
    }
    p.len = i;
    p.account[p.len] = -1;
    for(i = 0; i < p.len; i++)
    {
        sprintf(buff,"select * from user where id = %d and online = 1",p.account[i]);
        ret = mysql_query(&mysql, buff);
        if (!ret) {
            result = mysql_store_result(&mysql);    //返回查询结果
            
            if (row=mysql_fetch_row(result)) {
                strcpy(p.name[i] , row[1]);
            }
            else {
                p.account[i] = 0;
            }
        }
        
    }
    mysql_close(&mysql);
    return p;
}

int MYSQL_store_chat(int account, int send_account, char *mes)
{
    MYSQL_init();
    int ret;
    char buff[1000];
    sprintf(buff, "insert into chat_fri (id1,id2,mes)values (%d,%d,'%s')", account,send_account,mes);//连接两个字符串
    ret = mysql_query(&mysql,buff);
    if (!ret) {
        mysql_close(&mysql);
        return 0;
    }  
    else {
        mysql_close(&mysql);
        return -1;
     }
}

STR MYSQL_find_chat(int account, int send_account)
{
    int ret;
    char buff[1000];
    STR str;
    int i=0;
    sprintf(buff,"select * from chat_fri where (id1 = %d and id2 = %d) or (id1 =%d and id2 = %d)",account,send_account,send_account,account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        while (row=mysql_fetch_row(result)) {
            str.account[i] = atoi(row[0]);
            str.send_account[i] = atoi(row[1]);
            strcpy(str.mes[i], row[2]);
            i++;
        }
        str.len = i;
    }
    str.account[i] = -1;
    return str;
}

int MYSQL_dele_fri(int account,int send_account)
{
    char buff[1000];
    sprintf(buff,"delete from friends where (id1 = %d and id2 = %d) or (id1 =%d and id2 = %d)",account,send_account, send_account, account);
    mysql_query(&mysql, buff);
    return 0;
}

int MYSQL_creat_group(int account, char *mes) 
{
    int ret;
    int num_fields;

    char buff[1000];
    sprintf(buff, "insert into groups (account, group_name)values (%d,'%s')", account,mes);//连接两个字符串
    ret = mysql_query(&mysql,buff);
    if (!ret) {
        sprintf(buff, "select LAST_INSERT_ID()");//连接两个字符串
        ret = mysql_query(&mysql,buff);
        if (!ret) {
            result = mysql_store_result(&mysql);    //返回查询结果
            if (!result) {
                perror("login:mysql_store_result");
            }
            while (row=mysql_fetch_row(result)) {
                int id = atoi(row[0]);
                printf("群 %d 创建成功\n",id);
                sprintf(buff, "insert into g_meber (group_id, group_member,member_flag)values (%d,%d,1)", id,account);
                ret = mysql_query(&mysql,buff);
                mysql_close(&mysql);


                return id;
            }
        }
    }
    else {
        mysql_close(&mysql);
        return -1;
     }
}

int MYSQL_find_group_member(int account, int group_account)  //该群有这个账号，return 0；
{
    MYSQL_init();
    char buff[1000];
    int ret;
    sprintf(buff,"select * from g_meber  where group_member = %d and group_id = %d",account,group_account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        if ((mysql_fetch_row(result))) {
            mysql_close(&mysql);
            return 0;
        }
    }
     mysql_close(&mysql);
    return -1;
    
}

int MYSQL_find_group(int group_account)  //该群有这个账号，return 0；
{
    MYSQL_init();
    char buff[1000];
    int ret;
    sprintf(buff,"select * from groups  where id = %d",group_account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        if ((mysql_fetch_row(result))) {
            mysql_close(&mysql);
            return 0;
        }
    }
     mysql_close(&mysql);
    return -1;

}
int MYSQL_join_group(int account, int group_id)
{
    MYSQL_init();
    char buff[1000];
    int ret;
    sprintf(buff, "insert into g_meber (group_id,group_member,member_flag )values (%d,%d,0)", group_id,account);
    ret = mysql_query(&mysql,buff);
    if(!ret)
    {
        printf("群聊写入成功\n");
        mysql_close(&mysql);
        return 0;
    }
    mysql_close(&mysql);
    return -1; 
}

int MYSQL_quit_group(int account, int group_id)
{
    MYSQL_init();
    char buff[1000];
    int ret;
    sprintf(buff, "delete from g_meber where group_id = %d and group_member = %d", group_id,account);
    ret = mysql_query(&mysql,buff);
    if(!ret) {
        printf("退出群聊成功\n");
        mysql_close(&mysql);
        return 0;
    }
    mysql_close(&mysql);
    return -1;
}

int MYSQL_find_gowner(int account, int id)
{
    MYSQL_init();
    char buff[1000];
    int ret;
    sprintf(buff,"select * from groups  where id = %d and account = %d", id, account);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        if ((mysql_fetch_row(result))) {
            mysql_close(&mysql);
            return 0;
        }
    }
    mysql_close(&mysql);
    return -1;
}

int MYSQL_dele_group(int group_id) 
{
    MYSQL_init();
    char buff[1000];
    int ret;
    sprintf(buff, "delete from g_meber where group_id = %d", group_id);
    ret = mysql_query(&mysql,buff);
    if(!ret) {
        sprintf(buff, "delete from groups where id = %d", group_id);
        ret = mysql_query(&mysql,buff);
        if(!ret) {
            printf("删除群聊成功\n");
            mysql_close(&mysql);
            return 0;
        }
    }
    mysql_close(&mysql);
    return -1;
}

char * MYSQL_group_name(int id)
{
    MYSQL_init();
    int ret;
    char buff[1000];
    char tmp[100];
    char *p = tmp;
    int i=0;
    sprintf(buff,"select * from groups where id = %d ",id);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        while (row=mysql_fetch_row(result)) {
           strcpy(tmp, row[2]);
           return p;
        }
    }
    mysql_close(&mysql);
    return "fail";
}

GROUP MYSQL_group_mes(int group_id)
{
    MYSQL_init();
    int ret;
    GROUP group;
    char buff[1000];
    STR str;
    int i=0;
    sprintf(buff,"select * from g_meber where group_id = %d",group_id);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        while (row=mysql_fetch_row(result)) {
            group.account[i] = atoi(row[1]);
            group.flag[i] = atoi(row[2]);
            i++;
        }
        
    }
    else {
        group.account[0] = -1;
    }
    group.len = i;
    group.account[group.len] = -1;
    return group;
}

GROUP MYSQL_find_user(GROUP p)
{
    char buff[1000];
    int i,ret;
    for(i = 0; i < p.len; i++) {
        sprintf(buff,"select * from user where id = %d",p.account[i]);
        ret = mysql_query(&mysql, buff);
        if (!ret) {
            result = mysql_store_result(&mysql);    //返回查询结果
            if (!result) {
                perror("list_friend:mysql_store_result");
            }
            while (row=mysql_fetch_row(result)) {
                strcpy(p.name[i] , row[1]);
                p.online[i] =  atoi(row[3]);
                p.cli_fd[i] =  atoi(row[4]);
            }
        }
    }
    mysql_close(&mysql);
    return p;
}

int MYSQL_store_group(int group_id,  int group_member, char *mes)
{
    MYSQL_init();
    int ret;
    char buff[1000];
    sprintf(buff, "insert into chat_group (group_id,group_member,mes)values (%d,%d,'%s')", group_id,group_member,mes);
    ret = mysql_query(&mysql,buff);
    if (!ret) {
        mysql_close(&mysql);
        return 0;
    }  
    else {
        mysql_close(&mysql);
        return -1;
     }
}

STR_G MYSQL_find_chat_group(int account)
{
    int ret;
    char buff[1000];
    STR_G group;
    int i=0;
    sprintf(buff,"select * from chat_group where group_member = %d");
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        while (row=mysql_fetch_row(result)) {
            group.usr_account[i] = atoi(row[0]);
            strcpy(group.mes[i], row[2]);
            i++;
        }
        group.len = i;
    }
    group.usr_account[i] = -1 ;
    return group;
}

int MYSQL_set_up(int group_id, int set_account)
{
    MYSQL_init();
    char buff[1000]; 
    sprintf(buff,"update g_meber set member_flag = 2 where group_id = %d and group_member = %d",group_id , set_account);  
    printf("%s\n",buff);
    mysql_query(&mysql, buff);
    return 0;
}

int MYSQL_find_group_vip(int account, int group_id)
{
 MYSQL_init();
    char buff[1000];
    int ret;
    sprintf(buff,"select * from g_meber  where group_member = %d and group_id = %d and (member_flag != 0)",account,group_id);
    ret = mysql_query(&mysql, buff);
    if (!ret) {
        result = mysql_store_result(&mysql);    //返回查询结果
        if (!result) {
            perror("list_friend:mysql_store_result");
        }
        if ((mysql_fetch_row(result))) {
            mysql_close(&mysql);
            return 0;
        }
    }
     mysql_close(&mysql);
    return -1;
}

