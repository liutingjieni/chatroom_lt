/*************************************************************************
	> File Name: client_io.h
	> Author: 
	> Mail: 
	> Created Time: 2019年08月08日 星期四 15时55分56秒
 ************************************************************************/

#ifndef _CLIENT_IO_H
#define _CLIENT_IO_H
int send_login_PACK(int conn_fd);
void send_regist_PACK(int conn_fd);
int send_repasswd_PACK(int conn_fd);
void send_exit_PACK();
void send_addfriend_PACK();
int send_list_fri();
int send_online_fri();
void send_chat_fri();
void send_store_chat();
void send_dele_fri();
void send_creat_group();
void send_join_group();
void send_quit_group();
void send_dele_group();
void send_group_mes();
void send_chat_group();
void send_find_store_g();
void send_set_up();
void send_file();
void send_join_user();
void send_dele_user();

void *recv_PACK();
void recv_ADDFR_();
void recv_chat_fri();
void recv_chat_group();

int getch();
#endif
