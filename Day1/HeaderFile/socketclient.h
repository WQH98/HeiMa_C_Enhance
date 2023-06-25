// 防止头文件重复定义
#ifndef DAY1_SOCKETCLIENT_H
#define DAY1_SOCKETCLIENT_H
// 函数的声明

// 兼容C++编译器 如果是C++编译器 按C标准编译
#ifdef __cplusplus
extern "C"
{
#endif
    // 第一套接口
    // 初始化环境
    int scoketclient_init(void **handle);
    // 发送信息
    int socketclient_send(void *handle, void *buf, int len);
    // 接收信息
    int socketclient_recv(void *handle, void *buf, int len);
    // 释放资源
    int socketclient_destroy(void *handle);

    // 第二套接口
    // 初始化环境
    int scoketclient_init2(void **handle);
    // 发送信息
    int socketclient_send2(void *handle, void *buf, int len);
    // 接收信息
    int socketclient_recv2(void *handle, void **buf, int *len);
    // 释放信息
    int socketclient_free2(void **buf);
    // 释放资源
    int socketclient_destroy2(void **handle);


#ifdef __cplusplus
}
#endif
#endif
