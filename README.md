# chatroom_lt
### 项目概述
1. 本聊天室功能有: 
- 打印全部好友, 打印在线好友,添加好友, 删除好友, 好友聊天, 好友申请
- 打印群聊信息, 创建群聊, 加入群聊, 退出群聊, 删除群聊, 群组聊天, 设管理员. 群拉人, 群踢人等功能
- 发送文件, 接受文件
- 私聊盒子, 群聊盒子 
- 私聊记录, 群聊记录
- 支持离线消息
2. 介绍:
- 本项目基于C/S模型设计，分为客户端和服务器端两个部分，客户端直接连接到服务器，与服务器双向交换数据，服务器端用于接收客户端发来的消息，并转发给目标用户，所有数据的持久化工作也均由服务器端完成
- 服务端基于reactor模型, 采用epoll单线程模型
- 客户端分为两个线程, 一个负责完成与用户的交互, 发送请求给服务器, 另一个线程负责完成接受其余客户端发送的由服务端转发的消息完成实时聊天功能

2. 开发环境及使用工具
- 开发环境: deepin 15.9 X86_64
- 开发工具: Vim,gcc编译器

3. 使用说明
- 安装说明
```
git clone git@github.com:liutingjieni/chatroom_lt.git
cd chatroom_lt
```
- 使用说明
```
gcc server.c server_deal.c server_init.c MYSQL.c -I/usr/include/mysql/ -lmysqlclient -lpthread
./a.out
gcc client.c client_init.c client_io.c client_menu.c -lpthread
./a.out
```

提示：如果要进行跨级测试，请务必改变client_init.c 文件中#define IP "服务器IP地址"
