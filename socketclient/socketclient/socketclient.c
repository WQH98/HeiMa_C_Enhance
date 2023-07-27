#include "socketclient.h"

typedef struct socketHandle {

    char ip[50];            // IP
    unsigned int  port;     // 端口
    void *buf;              // 发送数据的缓冲区
    int len;
} socketHandle;

// 第一套接口
// 初始化环境
int socketclient_init(void **handle) {

    if(handle == NULL) {
        return -1;
    }

    socketHandle *hd = NULL;
    hd = (socketHandle*)malloc(sizeof(socketHandle));
    if(hd == NULL) {
        return -2;
    }
    memset(hd, 0, sizeof(socketHandle));
    // 结构体成员变量赋值
    strcpy(hd->ip, "255.255.255.255");
    hd->port = 8888;
    hd->buf = NULL;
    hd->len = 0;

    // 间接赋值 是指针存在的最大意义
    *handle = (void*)hd;

    return 0;
}
// 发送信息
int socketclient_send(void *handle, void *buf, int len) {

    if(handle == NULL || buf == NULL) {
        return -1;
    }

    socketHandle *hd = (socketHandle *)handle;

    // 先把上次分配的空间释放
    if(hd->buf != NULL) {
        free(hd->buf);
        hd->buf = NULL;
    }

    // 给结构体buf分配空间
    hd->buf = (char *)malloc(len);
    if(hd->buf == NULL) {
        return -2;
    }
    // memcpy
    memcpy(hd->buf, buf, len);
    hd->len = len;

    return 0;
}
// 接收信息
int socketclient_recv(void *handle, void *buf, int *len) {

    if(handle == NULL || buf == NULL) {
        return -1;
    }
    socketHandle *hd = (socketHandle *)handle;

    if(hd->buf != NULL) {
        memcpy(buf, hd->buf, hd->len);
        *len = hd->len;
    }
    else {
        return -2;
    }

    return 0;
}
// 释放资源
int socketclient_destroy(void *handle) {

    if(handle == NULL) {
        return -1;
    }
    socketHandle *hd = (socketHandle *)handle;
    if(hd != NULL) {
        if(hd->buf != NULL) {
            free(hd->buf);
            hd->buf = NULL;
        }
        free(hd);
        hd = NULL;
    }

    return 0;
}
// 第二套接口
// 初始化环境
int socketclient_init1(void **handle) {

    return 0;
}
// 发送信息
int socketclient_send1(void *handle, void *buf, int len) {

    return 0;
}
// 接收信息
int socketclient_recv1(void *handle, void *buf, int *len) {

    return 0;
}
// 释放资源
int socketclient_destroy1(void *handle) {

    return 0;
}
