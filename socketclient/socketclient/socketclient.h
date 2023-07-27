#ifndef SOCKETCLIENT_SOCKETCLIENT_H
#define SOCKETCLIENT_SOCKETCLIENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 第一套接口
// 初始化环境
int socketclient_init(void **handle);
// 发送信息
int socketclient_send(void *handle, void *buf, int len);
// 接收信息
int socketclient_recv(void *handle, void *buf, int *len);
// 释放资源
int socketclient_destroy(void *handle);
// 第二套接口
// 初始化环境
int socketclient_init1(void **handle);
// 发送信息
int socketclient_send1(void *handle, void *buf, int len);
// 接收信息
int socketclient_recv1(void *handle, void *buf, int *len);
// 释放资源
int socketclient_destroy1(void *handle);

#endif //SOCKETCLIENT_SOCKETCLIENT_H
