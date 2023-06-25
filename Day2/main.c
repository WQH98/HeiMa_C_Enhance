#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 01 作业
char *get_mem(int size) {
    char *p = NULL;
    p = (char *) malloc(size);
    return p;
}

void HomeWork() {
    char buf[100];
    int a = 10;
    int *p = NULL;
    p = &a;
    *p = 20;

    char *mp = get_mem(100);
    strcpy(mp, "abcdefg");
    if(mp != NULL) {
        printf("before = %d\r\n", mp);
        free(mp);  // 告诉系统 mp原来指向的内存可以被别人使用了
        printf("after = %d\r\n", mp);
        // 释放完 mp就是野指针 还是保存之前的地址 最好赋值为NULL
        mp = NULL;
    }
}

// 02 指针和指向的内存块是两个不同的概念
void APointerAndAPointedBlockOfMemoryAreTwoDifferentConcepts() {
    char *p = NULL;
    char buf[] = "abcdef";
    printf("before p = %d\r\n", p);
    // 改变指针变量的值
    p = buf;
    printf("after p = %d\r\n", p);
    // 指针变量和指针指向的内存是两个完全不同的概念
    p = p + 1; // 改变了指向变量的值 改变了指针的指向
    printf("p++ = %d\r\n", p);
    printf("buf = %s\r\n", buf);
    printf("*p = %s\r\n", p);
    // 改变指针指向的内存 并不会影响到指针的值
    buf[1] = '1';
    printf("改变指针指向的内存 并不会影响到指针的值\r\n");
    printf("after p = %d\r\n", p);
    printf("buf = %s\r\n", buf);

    *p = 'm';
    printf("after p = %d\r\n", p);
    printf("buf = %s\r\n", buf);

    // 写内存时 一定要确保内存可写
    char *buf2 = "abcdefg";  // 在文字常量区 内存不可修改
    // buf2[2] = '1';  // 修改会导致程序运行时候出错

    char buf3[] = "abcdefg"; // 会拷贝在栈区一份 栈区的内存可以修改
    buf3[1] = '1'; // 这样修改是可以的

    // 给p3指向的内存区域拷贝区域
    // char *p3 = NULL;
    // strcpy(p3, "1111");  // 这样拷贝是错误的 p3没有具体的指向内存
}

// 03 不断改变指针指向
void KeepChangingThePointer() {
    char *p = NULL;
    char *q = NULL;

    char buf[100] = "abcdefg";
    p = &buf[0];
    printf("p = %d %c\r\n", p, *p);

    p = &buf[1];
    printf("p = %d %c\r\n", p, *p);

    for(int i = 0; i < strlen(buf); i++) {
        p = &buf[i]; // p = buf + i
        printf("p = %d %c\r\n", p, *p);
    }

    q = (char *)malloc(100);
    if(q == NULL) {
        printf("malloc err\r\n");
    }
    strcpy(q, "hijklmn");
    for(int i = 0; i < strlen(q); i++) {
        p = q + i;
        printf("%c ", *p);
    }
    printf("\r\n");
}

// 04 通过指针间接赋值
int get_a() {
    int a = 10;
    return a;
}

void get_a2(int b) {
    b = 22;
}

void get_a3(int *b) {
    *b = 22;  // 通过*号操作内存
}

void get_a4(int *a1, int *a2, int *a3, int *a4) {
    *a1 = 1;
    *a2 = 2;
    *a3 = 3;
    *a4 = 4;
}

void fun2(int *p) {
    p = (int *)0x3344;
    printf("p = %p\r\n", p);
}

void fun3(int **p) {
    *p = (int *)0x5566;
    printf("*p = %p\r\n", *p);
}

void IndirectAssignmentThroughAPointer() {
    // 间接赋值的条件1 有2个变量 一个普通变量 一个指针变量
    int a = 100;
    int *p = NULL;
    // 建立关系 指针指向谁 就把谁的地址赋值给指针
    p = &a;
    // 通过*操作内存
    *p = 22;
    // 通过指针间接赋值
    // 1 两个变量
    // 2 建立关系
    // 3 通过*操作内存

    int b = get_a();
    printf("b = %d\r\n", b);

    get_a2(b);
    printf("b = %d\r\n", b);

    // 如果想通过形参改变实参的内存内容（值） 必须地址传递 使用实参和形参
    get_a3(&b); // 在函数调用时 建立关系
    printf("b = %d\r\n", b);

    int a1, a2, a3, a4;
    get_a4(&a1, &a2, &a3, &a4);
    printf("a1 = %d a2 = %d a3 = %d a4 = %d\r\n", a1, a2, a3, a4);

    // 一个变量 应该定义一个什么类型的指针保存他的地址
    // 在原来类型基础上加一个*
    // c原来没有* 保存c的地址要加一个*
    int c = 10;
    int *p1 = &c;
    // p1原来有一个* 保存p1的地址要加两个*
    int **q1 = &p;
    // t本来有10个* 保存t的地址要加11个*
    int **********t = NULL;
    int ***********t2 = &t;

    int *p2 = (int *)0x1122;
    printf("p2 = %p\r\n", p);
    fun2(p2);
    printf("p2 = %p\r\n", p);
    fun3(&p2);
    printf("p2 = %p\r\n", p);
}

// 05 指针做参数输入输出特性
void fun4(char *p) {
    // 给p指向的内存区域拷贝
    strcpy(p, "abcdefg");
}

void fun5(char *p) {
    // 养成习惯 先判断p为不为空
    if(p == NULL) {
        printf("err! p = NULL\r\n");
        return;
    }

    // 给p指向的内存区域拷贝
    strcpy(p, "abcdefg");
}

void fun6(char **p, int *len) {
    if(p == NULL) {
        return;
    }
    char *tmp = (char *) malloc(100);
    if(tmp == NULL) {
        return;
    }
    strcpy(tmp, "abcdefg");
    // 间接赋值
    *p = tmp;
    *len = strlen(tmp);

}

void PointersDoParameterInputOutputCharacteristics() {
    // 输入 主调函数分配内存
    char buf[100] = {0};
    fun4(buf);
    printf("buf = %s\r\n", buf);

    // err 向未指定区域的内存写值
    char *str = NULL;
    fun5(str);

    // 做输出 被调用函数分配内存 地址传递
    char *p = NULL;
    int len = 0;
    fun6(&p, &len);
    if(p != NULL) {
        printf("p = %s, len = %d\r\n", p, len);
    }
}

// 06 字符串的初始化
// C语言没有字符串类型 是通过字符数组来模拟的
// C语言字符串 以字符'\0'或数字0结尾
void StringInitialization() {
    // 不指定长度 没有0结束符 有多少个元素就有多长
    char buf[] = {'a', 'b', 'c', 'd'};
    printf("buf = %s\r\n", buf); // 不指定长度就打印 没有结尾的结束符 会打印乱码
    // 指定长度 后面没有赋值的元素 自动补0
    char buf1[100] = {'a', 'b', 'c', 'd'};
    printf("buf1 = %s\r\n", buf1);
    // 所有元素赋值为0
    char buf2[100] = {0};
    // 数组越界
    // char buf3[2] = {'1', '2', '3'};

    char buf4[50] = {'1', 'a', 'b', '0', '7'};
    printf("buf4 = %s\r\n", buf4);

    char buf5[50] = {'1', 'a', 'b', 0, '7'};
    printf("buf5 = %s\r\n", buf5);

    char buf6[50] = {'1', 'a', 'b', '\0', '7'};
    printf("buf6 = %s\r\n", buf6);

    // 最常用的是使用字符串初始化
    char buf7[] = "abcdef";
    // strlen：测字符串长度 不包含数字0 字符'\0'
    // sizeof：测数组长度 包含数字0 字符'\0'
    printf("strlen = %d, sizeof = %d\r\n", strlen(buf7), sizeof(buf7));

    char buf8[100] = "abcdef";
    printf("strlen = %d, sizeof = %d\r\n", strlen(buf8), sizeof(buf8));

    char buf9[] = "abcdefg";
    // 访问数组方法 []法
    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", buf9[i]);
    }
    printf("\r\n");

    // 访问数组方法 指针法
    // 数组名字就是数组首元素的地址
    char *p = NULL;
    p = buf9;
    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", p[i]);
    }
    printf("\r\n");

    // buf和p完全等价吗？
    // p++;
    // buf++;
    // buf只是一个常量 不能修改

    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", *(p + i));
    }
    printf("\r\n");

    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", *(buf9 + i));
    }
    printf("\r\n");
}

// 07 字符串拷贝函数的实现
void my_strcpy(char *dst, char *src) {
    int i = 0;
    for(i = 0; *(src + i) != '\0'; i++) {
        *(dst + i) = *(src + i);
    }
    *(dst + i) = '\0';
}

void my_strcpy2(char *dst, char *src) {
    while(*src != 0) {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

void my_strcpy3(char *dst, char *src) {
    while(*src != 0) {
        // *号和++优先级相同 采取从右到左
        // 先用再加
        // 就相当于*dst = *src; dst++; src++;
        *dst++ = *src++;
    }
    *dst = '\0';
}

// 返回值：成功为0 失败返回非0
// 判断形参指针是否为NULL
// 最好不要直接使用形参
// 可以使用辅助变量把形参接过来
int my_strcpy4(char *dst, char *src) {
    if(dst == NULL || src == NULL) {
        return -1;
    }
    // *dst = *src;
    // dst++;
    // src++;
    // 判断*dst是否为0 为0跳出循环
    while(*dst++ = *src++) {
        NULL;
    }
    return 0;
}

void StringCopyFunction() {
    char src[] = "abcdefg";
    char dst[100];
    int i = 0;
    for(i = 0; src[i] != 0; i++) {
        dst[i] = src[i];
    }
    // 补结束符
    dst[i] = 0;
    printf("dst = %s\r\n", dst);

    memset(dst, 0, 100);
    my_strcpy(dst, src);
    printf("my_strcpy dst = %s\r\n", dst);

    memset(dst, 0, 100);
    my_strcpy2(dst, src);
    printf("my_strcpy2 dst = %s\r\n", dst);

    memset(dst, 0, 100);
    my_strcpy3(dst, src);
    printf("my_strcpy3 dst = %s\r\n", dst);

    int ret = 0;
    memset(dst, 0, 100);
    ret = my_strcpy4(dst, src);
    if(ret != 0) {
        printf("my strcpy4 err:%d\r\n", ret);
    }
    printf("my_strcpy4 dst = %s\r\n", dst);

}

// strstr中的while和do_while模型
void TheWhileAndDoWhileModelsInStrstr() {
    char *p = "11abcd11122abcd3333322abcd3333322qqqabcd";
    int n = 0;
    do{
        p = strstr(p, "abcd");
        if(p != NULL) {
            n++; //累计地址
            // 重新设置查找的起点
            p = p + strlen("abcd");
        }
        else { // 如果没有匹配的字符串 就跳出循环
            break;
        }
    }while(*p != 0); // 如果没有到字符串结尾
    printf("n = %d\r\n", n);
}

void TheWhileAndDoWhileModelsInStrstr1() {
    char *p = "11abcd11122abcd3333322abcd3333322qqqabcd";
    int n = 0;

    while((p = strstr(p, "abcd")) != NULL) {
        // 能进来肯定就是有匹配的子串
        // 重新设置起点位置
        p += strlen("abcd");
        n++;
        if(*p == 0) {   //如果到结束符
            break;
        }
    }

    printf("n = %d\r\n", n);
}

// 正确返回0 错误返回-1
int my_strstr(char *p, int *n) {

    // 辅助变量
    int i = 0;
    char *tmp = p;

    if(p == NULL) {
        return -1;
    }

    while((tmp = strstr(tmp, "abcd")) != NULL) {
        // 能进来肯定就是有匹配的子串
        // 重新设置起点位置
        tmp += strlen("abcd");
        i++;
        if(*tmp == 0) {   //如果到结束符
            break;
        }
    }
    // 间接赋值
    *n = i;
    return 0;
}

void TheWhileAndDoWhileModelsInStrstr2() {
    char *p = "11abcd11122abcd3333322abcd3333322qqq";
    int n = 0;
    int ret = 0;

    ret = my_strstr(p, &n);
    if(ret != 0) {
        printf("err: not found\r\n");
    }

    printf("n = %d\r\n", n);
}

// 函数作用 返回两头堵模型中间字符串个数
int Two_endBlockingModel_fun(char *p, int *n) {
    if(p == NULL || n == NULL) {
        return -1;
    }

    int begin = 0;
    int end = (strlen(p) - 1);

    // 先从左边开始 如果当前字符为空 而且没有遇到结束符
    while(isspace(p[begin]) && p[begin] != 0) {
        begin++;  // 位置从右往左移动一位
    }

    // 再从右边开始 如果当前字符为空 而且没有遇到结束符
    while(isspace(p[end]) && p[end] != 0) {
        end--;   // 位置从左往右移动一位
    }

    *n = end - begin + 1;
    return 0;
}

// 函数作用 返回两头堵模型中具体的字符串
int Two_endBlockingModel_fun2(char *p, char *buf) {
    int n = 0;

    if(p == NULL || buf == NULL) {
        return -1;
    }

    int begin = 0;
    int end = (strlen(p) - 1);

    // 先从左边开始 如果当前字符为空 而且没有遇到结束符
    while(isspace(p[begin]) && p[begin] != 0) {
        begin++;  // 位置从右往左移动一位
    }

    // 再从右边开始 如果当前字符为空 而且没有遇到结束符
    while(isspace(p[end]) && p[end] != 0) {
        end--;   // 位置从左往右移动一位
    }

    n = end - begin + 1;

//    for(int i = 0; i < n; i++, begin++) {
//        buf[i] = p[begin];
//    }

    strncpy(buf, p+begin, n);

    buf[n] = 0;

    return 0;
}

int Two_endBlockingModel() {
    char *p = "      abcdeewrwerfg      ";
    int n = 0;
    int ret = 0;
    int ret2 = 0;
    char buf[100] = {0};

    ret = Two_endBlockingModel_fun(p, &n);
    ret2 = Two_endBlockingModel_fun2(p, buf);

    if(ret != 0) {
        return ret;
    }

    if(ret2 != 0) {
        return ret2;
    }

    printf("buf = %s\r\n", buf);
    printf("n = %d\r\n", n);

    return 0;
}

int main() {
    Two_endBlockingModel();
    printf("Hello, World!\n");
    return 0;
}
