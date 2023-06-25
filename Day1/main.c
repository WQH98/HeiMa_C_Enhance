#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socketclient.h"

// 空类型
void VoidType() {
    void *p = NULL;
    char buf[128] = "abcdefg";
    p = buf;  // 指向这个地址 使用时转化为实际类型指针
    printf("p = %s\r\n", (char *)p);

    int a[128] = {1, 2, 3, 4};
    p = a;
    for(int i = 0; i < 4; i++) {
        printf("%d ", *((int*)p+i));
    }
    printf("\r\n");

    int b[3] = {1, 2, 3};
    int c[3];
    memcpy(c, b, sizeof(b));
    for(int i = 0; i < 3; i++) {
        printf("%d ", c[i]);
    }
    printf("\r\n");

    char str[] = "abcdef";
    char dst[128];
    memcpy(dst, str, sizeof(str));
    printf("dst = %s\r\n", dst);
}

// 指针也是一种数据类型
void APointerIsAlsoADataType() {
    int *p = NULL;
    char **********q = NULL;
    printf("sizeof(p) = %d sizeof(q) = %d\r\n", sizeof(p), sizeof(q));
}

// 栈地址生长方向
void StackAddressGrowthDirection() {
    int a;
    int b;
    printf("a = %d, b = %d\r\n", &a, &b);
}

// 静态局部变量的使用
char *getA() {
    static int a = 10;

    return &a;
}

void UseOfStaticLocalVariables() {
    int *p = getA();
    printf("*p = %d\r\n", *p);
}

// 堆栈区分析
// 栈区
char *get_str() {
    char str[] = "abcdefg";
    printf("str = %s\r\n", str);
    // 返回首地址 返回的地址是容易变的
    return str;
}
// 堆区
char *get_str3() {
     char *tmp = (char*)malloc(100);
     if(tmp == NULL) {
         return NULL;
     }
     strcpy(tmp, "abcdefg");
     return tmp;
}

void StackAreaAnalysis() {
    char buf[128] = {0};
//    strcpy(buf, get_str()); // 说明不了问题 因为有可能编译器会把str的内容拷贝完再释放
//    printf("buf = %s\r\n", buf); // 乱码 不确定
    char *p = NULL;
    p = get_str3();
    if(p != NULL) {
        printf("p = %s\r\n", p);
        free(p);
        p = NULL;
    }
}

// 全局区分析
char *get_str1() {
    char *p = "abcdef";  // 文字放在文字常量区
    return p;
}

char *get_str2() {
    char *q = "abcdef";  // 文字放在文字常量区
    return q;
}

void Global_Area_Analysis(void) {
    char *p = NULL;
    char *q = NULL;

    p = get_str1();
    q = get_str2();
    // %s：指针指向内存区域的内容
    // %d：打印p本身的值 也就是地址
    printf("p = %s, p = %d\r\n", p, p);
    printf("q = %s, q = %d\r\n", q, q);
}

// 变量赋值
void VariableAssignment(void) {
    // 变量本质：一段连续内存空间别名
    // 变量相当于门牌号 内存相当于空间
    int a;
    int *p = NULL;
    // 直接赋值
    a = 10;
    printf("a = %d\r\n", a);
    // 间接赋值
    printf("&a = %d\r\n", &a);
    p = &a;
    printf("p = %d\r\n", p);
    *p = 22;
    printf("*p = %d, a = %d\r\n", *p, a);
}

// 类型别名
void TypeAlias(void) {
    typedef unsigned int u32;
    u32 t;
    // typedef通常与结构体结合使用
    struct MyStruct
    {
        int a;
        int b;
    };
    struct MyStruct m1;
    // MyStruct m2; //error
    // 在使用结构体定义变量的时候可以少写几个单词
    // typedef把struct MyStruct2规定别名为TMP
    // struct MyStruct2 == TMP
    typedef struct MyStruct2
    {
        int a;
        int b;
    }TMP;
    TMP m3;

    typedef struct{
        int a;
        int b;
    }TMP2;
    TMP2 m4;
    m4.a = 100;
    printf("m4.a = %d\r\n", m4.a);
}

// 数据类型本质
void DataType(void) {
    int a;      // 告诉编译器 分配4个字节
    int b[10];  // 告诉编译器 分配40个字节
    // 类型的本质：固定内存块大小别名 可以通过sizeof测试
    printf("sizeof(a) = %d, sizeof(b) = %d\r\n", sizeof(a), sizeof(b));
    // 数组名字  数组首元素地址  数组首地址
    // b &b 的数据类型不一样
    // b是数组首元素地址 一个元素4字节 +1 == +4字节
    // &b是整个数组的首地址 一个数组有40字节 +1 == +40字节
    printf("b:%d   &b:%d\r\n", b, &b);
    printf("b+1:%d   &b+1:%d\r\n", b+1, &b+1);

    // 指针类型长度 32位程序 长度4
    //            64位程序 长度8
}


// 如果数组作为函数参数，数组形参退化为指针
// a当做指针用 指针类型 32位 用sizeof显示长度4个字节
//                   64位 用sizeof显示长度8个字节
void printf_array(int a[], int len) {
    int i;
    for(i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\r\n");
}

void sort_array(int a[], int len) {
    int i, j, tmp;
    // 选择法排序
    for(i = 0; i < len-1; i++) {
        for(j = i+1; j < len; j++) {
            if(a[i] > a[j]) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

// 排序函数
void rank(void) {
    int a[] = {10, 7, 1, 9, 4, 6, 7, 3, 2, 0};
    int n;

    n = sizeof(a) / sizeof(a[0]);

    printf("before rank\r\n");
    printf_array(a, n);

    sort_array(a, n);

    printf("before start\r\n");
    printf_array(a, n);
}

int main(void) {
    VoidType();
    printf("Hello, World!\n");
    // 加这一句是为了能看到函数执行结果
    // system("pause");
    return 0;
}
