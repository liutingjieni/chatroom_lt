/*************************************************************************
	> File Name: client_menu.c
	> Author: 
	> Mail: 
	> Created Time: 2019年08月07日 星期三 11时01分59秒
 ************************************************************************/
#include "client_io.h"
#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>


char login_menu();
char main_menu();
void  main_login(int);
void deal(char choice);


char login_menu()
{
    char choice;
    printf("\n\t\t\33[1m\033[;34m*******************************\033[0m\n");
    printf("\t\t\033[;34m*\033[0m        1. 登录             \033[;34m*\033[0m \n");
    printf("\t\t\033[;34m*\033[0m        2. 注册             \033[;34m*\033[0m \n");
    printf("\t\t\033[;34m*\033[0m        3. 修改密码         \033[;34m*\033[0m \n");
   
    printf("\t\t\033[;34m*\033[0m        0. 退出             \033[;34m*\033[0m \n");
    printf("\t\t\033[;34m*******************************\033[0m\n");  
    choice = getch();
       
    return choice;
}

char main_menu()
{
    char choice;
    do {
        printf("\n\t\t***************************\n");
        printf("\t\t*        a.  全部好友       *\n");
        printf("\t\t*        b.  在线好友       *\n");
        printf("\t\t*        c.  添加好友       *\n");
        printf("\t\t*        d.  删除好友       *\n");
        printf("\t\t*        e.  群聊信息       *\n");
        printf("\t\t*        f.  创建群聊       *\n");
        printf("\t\t*        g.  加入群聊       *\n");
        printf("\t\t*        h.  退出群聊       *\n");
        printf("\t\t*        i.  删除群聊       *\n");
        printf("\t\t*        j.  好友聊天       *\n");
        printf("\t\t*        k.  群组聊天       *\n");
        printf("\t\t*        l.  发送文件       *\n");
        printf("\t\t*        m.  好友申请       *\n");
        printf("\t\t*        n.  私聊盒子       *\n");
        printf("\t\t*        o.  群聊盒子       *\n");
        //printf("\t\t*     .file message box %d  *\n",m_recv_num_file_mes);
        printf("\t\t*        p.  私聊记录       *\n");
        printf("\t\t*        q.  群聊记录       *\n");
        printf("\t\t*        r.  设管理员       *\n");
        printf("\t\t*        s.  群拉人         *\n");
        printf("\t\t*        t.  群踢人         *\n");
        printf("\t\t*        0.  退出           *\n");
        printf("\t\t****************************\n");
        choice = getch();
        deal(choice);
        printf("按任意键返回主菜单\n");
        //getch();
    }while(1);
} 

void  main_login(int cli_fd)
{
    char choice;
    int ret;
    choice = login_menu();
     pthread_t recv_tin;
    switch (choice){
    case '1':
        if (send_login_PACK(cli_fd) == 0) {
            pthread_create(&recv_tin, NULL, recv_PACK, NULL);
            main_menu();
        }
        else {
            main_login(cli_fd);
            printf("登录失败，请重新选择登录注册或退出！\n");
        }
        break;
    case '2':
        send_regist_PACK(cli_fd);
        main_login(cli_fd);
        break;
    case '3':
        if (send_repasswd_PACK(cli_fd) == 0) {
            main_login(cli_fd);
            printf("修改成功,请重新选择登录呀！！\n");
        }
        else {
            main_login(cli_fd);
            printf("修改失败！！\n");
        }
    case '0':
        exit(0);
    default :
        printf("小傻逼你好好输!!!\n");
        getch();
        main_login(cli_fd);
    }

}

void deal(char choice)
{
    
    switch (choice)
    {
        case '0':
            send_exit_PACK();
            exit(0);
            break;
        case 'a':
            send_list_fri();
            break;
        case 'b':
            send_online_fri();
            break;
        case 'c':
            send_addfriend_PACK();
            break;
        case 'd':
            send_dele_fri();
            break;
        case 'e':
            send_group_mes();
            break;
        case 'f':
            send_creat_group();
            break;
        case 'g':
            send_join_group();
            break;
        case 'h':
            send_quit_group();
            break;
        case 'i':
            send_dele_group();
            break;
        case 'j':
            send_chat_fri();
            break;
        case 'k':
            send_chat_group();
            break;
        case 'l':
            send_file();
            break;
        case 'm':
            recv_ADDFR_();
            break;
        case 'n':
            recv_chat_fri();
            break;
        case 'o':
            recv_chat_group();
            break;
        case 'p':
            send_store_chat();
            break;
        case 'q':
            send_find_store_g();
            break;
        case 'r':
            send_set_up();
            break;
        case 's':
            send_join_user();
            break;
        case 't':
            send_dele_user();
            break;
        default:
            printf("狗子你要好好输入啊！！！\n");
            break;
    }
}



