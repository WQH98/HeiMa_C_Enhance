#include <stdio.h>
#include "socketclient.h"

int main() {

    void *handle = NULL;
    int ret = 0;

    // 初始化环境
    ret = socketclient_init(&handle);
    if(ret != 0) {
        printf("socketclient_init failed:%d\r\n", ret);
        return ret;
    }

    // 发送信息
    char buf[100] = "abcdefg";
    ret = socketclient_send(&handle, buf, strlen(buf));
    if(ret != 0) {
        printf("socketclient_send failed:%d\r\n", ret);
        return ret;
    }
    printf("send success\r\n");
    memset(buf, 0, sizeof(buf));

    // 接收信息
    int len = 0;
    ret = socketclient_recv(handle, buf, &len);
    if(ret != 0) {
        printf("socketclient_recv failed:%d\r\n", ret);
        return ret;
    }
    printf("buf = %s, len = %d\r\n", buf, len);

    // 释放资源
    ret = socketclient_destroy(handle);
    if(ret != 0) {
        printf("socketclient_destroy failed:%d\r\n", ret);
        return ret;
    }
    handle = NULL;


    printf("Hello, World!\n");
    return 0;
}
