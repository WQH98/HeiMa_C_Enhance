#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 1 const的使用
typedef struct {
    int a;
    int b;
} MyStruct;

void fun1_0(MyStruct *p) {
    // 指针能变 指针指向的内存也可以变
    p = NULL; // ok
    p->a = 10; // ok
}

void fun1_1(MyStruct const *p) {
    // 指针指向的地址可以变
    p = NULL;  // ok
    // 指针指向的内存区域不可修改
    // p->a = 10; // err
}

void fun1_2(MyStruct * const p) {
    // 指针指向的地址不可以变
    // p = NULL;  // err
    // 指针指向的内存区域可以修改
    p->a = 10; // ok
}

void fun1_3(MyStruct const * const p) {
    // p 只读
    // 指向的地址不可以变 指向的内存区域也不可以修改
    // 可以用临时变量来修改
    MyStruct tmp;
    tmp.a = p->a;
}


void UseOfConst() {
    // const 修饰一个变量为只读
    const int a = 10;
    // a = 100;   // err

    // 指针变量和指针指向的内存是两个不同的概念
    char buf[] = "abcdefg";

    // 从左往右看 跳过类型 看修饰哪个字符
    // 如果是* 说明指针指向的内存不能改变
    // 如果是指针变量 说明指针的指向不能改变 指针的值不能修改
    // 修饰* *是取指针指向的内容 所以内容不能变
    // 修饰变量 变量里面存的是地址 说以地址不能变
    const char *p = buf;
    // 等价于上面 char const *p = buf;
    // p[1] = '2';   //err
    // p = "aasdasdasd"; // ok

    // 说明指针指向的地址是固定死的 不能再去指向别的地址 可以通过p1来改变buf的值
    char *const p1 = buf;
    // p1[2] = '3';  // ok
    // p1 = "sasdasdadas"; // err

    // p2为只读 指向不能变 指向的内存也不能变
    const char * const p2 = buf;
    // 等价于上面 char const * const p2 = buf;
    // p2[2] = '3';  // err
    // p2 = "sasdasdadas"; // err

    // C语言中的const不是真正的const
    // 可以通过指针的指向改变这个值
    // 在C++中可以避免
    const int b = 10;
    printf("b = %d\r\n", b);
    int *q = &b;
    *q = 100;
    printf("b = %d\r\n", b);
}

// 在别的文件中引用的const变量 只能声明 不能再赋值
// 使用extern关键字声明
// 使用const修饰的变量 再定义时必须要初始化

// 2 二级指针做参数输出特性
// 值传递 形参的任何修改不会影响到实参
int getMem(char *p) {
    p = (char *)malloc(sizeof(char) * 100);
    if(p == NULL) {
        return -1;
    }
    strcpy(p, "abcdefg");
    printf("p = %s\r\n", p);

    return 0;
}

// 地址传递 形参的任何修改会影响到实参
int getMem2(char **p) {
    if(p == NULL) {
        return -1;
    }

    char *tmp = (char *)malloc(100);
    if(tmp == NULL) {
        return -2;
    }

    strcpy(tmp, "abcdefg");

    *p = tmp;

    printf("*p = %s\r\n", *p);

    return 0;
}

// 函数输入是在主调函数分配内存
// 函数输出是在被调函数分配内存
// 二级指针主要是做输入
void TheSecondaryPointerIsTheParameterOutputFeature() {
    char *p = NULL;
    int ret = 0;

    ret = getMem2(&p);
    if(ret != 0) {
        printf("getMem err: %d\r\n", ret);
    }
    printf("p = %s\r\n", p);

    if(p != NULL) {
        free(p);
        p = NULL;
    }
}

// 3二级指针做输入
// void printf_array(char *p[], int n) {   // 与下面等价
void printf_array(char **p, int n) {
    for(int i = 0; i < n; i++) {
        printf("%s, ", p[i]);
    }
    printf("\r\n");
}

void sort_array(char **p, int n) {
    // 选择法排序
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(strcmp(p[i], p[j]) > 0) {
                char *tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
}

// 第一种内存模型
void TheFirstMemoryModel() {
    int a;
    int b;
    int c;
    int d[3];


    // 每个类型都是char*
    char *p0 = "0000";
    printf("%s\r\n", p0);
    char *p1 = "1111";
    char *p2 = "2222";
    char *p3 = "3333";
    // 指针数组 指针的数组 他是一个数组 每一个元素都是指针char*
    char *p[] = {"1111", "3333", "0000", "2222"};
    // char **qq[] = {"1111", "3333", "0000", "2222"};  // err
    // 当数组不指定长度的时候可以这么计算数组长度
    int n = sizeof(p) / sizeof(p[0]);
    printf("sizeof(p) = %d\tsizeof(p[0]) = %d\r\n", sizeof(p), sizeof(p[0]));
    int i = 0;
    for(i = 0; i < n; i++) {
        printf("%s\r\n", p[i]);
    }
    // 当数组已经指定固定长度时候 这么做会算出数组的总长度
    char *q[10] = {"0000", "1111", "2222", "3333"};
    printf("sizeof(q) = %d\tsizeof(q[0]) = %d\r\n", sizeof(q), sizeof(q[0]));

    printf("before: \r\n");
    printf_array(p, n);

    // 选择法排序
    sort_array(p, n);

    printf("end: \r\n");
    printf_array(p, n);
}



// 第二种内存模型 指针二维数组
// 这样打印会导致步长不一致
void printf_array1(char **a, int n) {
    printf("a = %d, a+1 = %d\r\n", a, a+1);
    for(int i = 0; i < n; i++) {
        // 以下三种方式都可以正常打印
        // 首行地址 和首行首元素地址的值是一样的
        // printf("%s\r\n", a[i]);
        // printf("%s\r\n", a+i);
        printf("%s\r\n", *(a+i));
    }
}

void printf_array2(char a[4][30], int n) {
    printf("a = %d, a+1 = %d\r\n", a, a+1);
    for(int i = 0; i < n; i++) {
        // 以下三种方式都可以正常打印
        // 首行地址 和首行首元素地址的值是一样的
        // printf("%s\r\n", a[i]);
        // printf("%s\r\n", a+i);
        printf("%s, ", *(a+i));
    }
    printf("\r\n");
}

void sort_array1(char a[4][30], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
           if(strcmp(a[i], a[j]) > 0) {
               // 交换的是内存块
               char tmp[30];
               strcpy(tmp, a[i]);
               strcpy(a[i], a[j]);
               strcpy(a[j], tmp);
           }
        }
    }
}

void TheSecondMemoryModel() {
    char a0[30] = "2222222222";
    char a1[30] = "1111111111";
    char a2[30] = "bbbbbbbbbb";
    char a3[30] = "aaaaaaaaaa";

    // 4个a[30]的一维数组 二维数组
    // a带边首行地址 首行地址和首行首元素地址有区别 但是他们的值是一样的
    // 区别：步长不一样
    char a[4][30] = {"2222222222", "1111111111", "bbbbbbbbbb", "aaaaaaaaaa"};
    // a[0] = "2222222222"
    printf("a:%d, a+1:%d\r\n", a, a+1);
    int na = sizeof(a) / sizeof(a[0]);
    printf("na = %d\r\n", na);

    // 不写第一个[]值也是有条件的 必须要初始化数组里面的值
    char aa[][30] = {"2222222222", "1111111111", "bbbbbbbbbb", "aaaaaaaaaa"};
    int naa = sizeof(aa) / sizeof(aa[0]);
    printf("naa = %d\r\n", naa);

    // 与一维数组一样 求数组长度时候尽量不要选择固定长度的
    char aaa[10][30] = {"2222222222", "1111111111", "bbbbbbbbbb", "aaaaaaaaaa"};
    int naaa = sizeof(aaa) / sizeof(aaa[0]);
    printf("naaa = %d\r\n", naaa);

    char b[30];
    printf("&b:%d, &b+1:%d\r\n", &b, &b+1);

    printf("before:\r\n");
    printf_array2(a, na);

    printf("after:\r\n");
    sort_array1(a, na);
    printf_array2(a, na);

}


// 第三种内存模型
void TheThirdMemoryModel() {
    char *p0 = NULL;
    p0 = (char*)malloc(100);
    strcpy(p0, "abcdef");

    // 10个char*
    char *p[10] = {0};
    for(int i = 0; i <10; i++) {
        p[i] = malloc(100);
        strcpy(p[i], "abcdef");
    }
    int a = 10;
    int *q = (int *)malloc(10 * sizeof(int));

    // 动态分配一个数组 但是数组每个元素都是char*
    // char *ch[10]
    int n = 10;
    char **buf = (char **)malloc(n * sizeof(char *));   // char *buf[10]
    if(buf == NULL) {
        printf("buf = NULL\r\n");
    }
    for(int i = 0; i < n; i++) {
        buf[i] = (char *)malloc(30 * sizeof(char));
        char str[30];
        sprintf(str, "test%d%d", i, i);
        strcpy(buf[i], str);
    }

    for(int i = 0; i < n; i++) {
        printf("%s ", buf[i]);
    }
    printf("\r\n");

    for(int i = 0; i < n; i++) {
        if(buf[i] != NULL) {
            free(buf[i]);
            buf[i] = NULL;
        }
    }
    if(buf != NULL) {
        free(buf);
        buf = NULL;
    }
}

char **getMem3(char **buf, int n) {
    buf = (char **)malloc(n * sizeof(char *));
    if(buf == NULL) {
        return NULL;
    }
    for(int i = 0; i < n; i++) {
        buf[i] = (char *)malloc(30 * sizeof(char));
        char str[30];
        sprintf(str, "test%d%d", i, i);
        strcpy(buf[i], str);
    }
    return buf;
}

void printf_buf(char **buf, int n) {
    for(int i = 0; i < n; i++) {
        printf("%s ", buf[i]);
    }
    printf("\r\n");
}

void free_buf(char **buf, int n) {
    for(int i = 0; i < n; i++) {
        if(buf[i] != NULL) {
            free(buf[i]);
            buf[i] = NULL;
        }
    }
    if(buf != NULL) {
        free(buf);
        buf = NULL;
    }
}

void TheThirdMemoryModel_main() {
    char **buf = NULL;
    int n = 3;
    buf = getMem3(buf, n);
    if(buf == NULL) {
        printf("getMem3 err\r\n");
    }

    printf_buf(buf, n);

    free_buf(buf, n);

    buf = NULL;

}

// 作业5
// "abcd11111abcd2222abcdqqqqq"
// "dcba11111dcba2222dcbaqqqqq"
// src：原字符串
// dst：生成的或需要填充的字符串
// sub：需要查找的字符串
// new_sub：替换的新字符串
// return：0成功  -1失败
int replaceSubstr(char *src, char **dst, char *sub, char *new_sub) {

    if(src == NULL || sub == NULL || new_sub == NULL || dst == NULL) {
        return -1;
    }

    char *p = src;
    char *tmp = NULL;
    char *src_old = src;
    tmp = (char *)malloc(100 * sizeof(char));

    strnset(tmp, 0, 100);

    while(1) {
        src_old = p;
        p = strstr(p, sub);
        if(p == NULL) {
            strcat(tmp, src_old);
            break;
        }

        strncat(tmp, src_old, p - src_old);
        p += strlen(sub);
        strncat(tmp, new_sub, strlen(new_sub));
    }

    printf("tmp = %s\r\n", tmp);

    *dst = tmp;

    return 0;
}

void work5(void) {
    char *str = "2233abcd11111abcd2222abcdqqqqq";
    char *dst = NULL;
    char sub[] = "abcd";
    char new_sub[] = "dcba";
    int ret = 0;
    ret = replaceSubstr(str, &dst, sub, new_sub);
    if(ret == 0) {
        printf("dst = %s\r\n", dst);
    }
    else {
        printf("err %d\r\n", ret);
    }

    if(dst != NULL) {
        free(dst);
        dst = NULL;
    }
}

int spitString(const char *str, char c, char buf[10][30], int *count) {

    if(str == NULL || buf == NULL || count == NULL) {
        return -1;
    }

    int i = 0, j = 0;
    char *p = NULL;
    char *ret_p = NULL;
    int ret_p_size = 0;
    p = (char *)malloc(100 * sizeof(char));
    strcpy(p, str);

    while(1) {
        ret_p = strchr(p, c);
        // printf("ret_p = %s\t", ret_p);
        if(ret_p == NULL) {
            break;
        }
        ret_p_size = strlen(p) - strlen(ret_p);
        for(j = 0; j < ret_p_size; j++) {
            buf[i][j] = p[j];
        }

        buf[i][j] = '\0';

        i++;

        p += ret_p_size + 2;
    }
    // 注释以后就没有打印结果了
//    for(int temp = 0; temp < i; temp ++) {
//        printf("buf[%d] = %s\r\n", temp, buf[temp]);
//    }
    count = &i;
    if(p != NULL) {
        free(p);
        p = NULL;
    }

    return 0;
}


// 作业6
int spitString2(const char *str, char c, char **myp, int *count) {

    if(str == NULL || myp == NULL || count == NULL) {
        return -1;
    }

    static int i = 0, j = 0;

    char *find_c = NULL;
    int p_len = 0, find_c_len = 0;
    char *temp = (char *)malloc(100 * sizeof(char));
    char *p = (char *) malloc(100 *sizeof(char));
    strcpy(p, str);


    while(1) {
        p_len = (int)strlen(p);
        find_c = strchr(p, c);
        if(find_c == NULL) {
            break;
        }
        find_c_len = (int)strlen(find_c);

        for(i = 0; i < p_len - find_c_len; i++) {
            temp[i] = p[i];
        }
        temp[i] = '\0';
        myp[j] = (char *)malloc(100 * sizeof(char));
        strcpy(myp[j], temp);

        j++;
        //printf("temp = %s\t", temp);
        //printf("j = %d\tmyp = %s\t", j, myp[j]);

        p += p_len - find_c_len + 2;
        //printf("find_c = %s\r\n", find_c);
    }
    *count = j;
    return 0;
}

void work6() {
    char *str = "abcdef, acccd, eeee, aaaa, e3eeee, ssss,";
    int count = 0;
    char **myp = (char **) malloc(200 * sizeof(char *));
    int ret = spitString2(str, ',', myp, &count);
    printf("ret = %d\tcount = %d\r\n", ret, count);
    for(int i = 0; i < count; i++) {
        printf("myp[%d] = %s\r\n", i, myp[i]);
    }
    for(int i = 0; i < count; i++) {
        if(myp[i] != NULL) {
            free(myp[i]);
        }
        myp[i] == NULL;
    }
}

int replacesubstr_heima(char *src, char **dst, char *sub, char *new_sub) {

    if(src == NULL || dst == NULL || sub == NULL || new_sub == NULL) {
        return -1;
    }

    char *start = src;
    char *p = NULL;
    char tmp[512] = {0};
    int len = 0;

    do {
        p = strstr(start, sub);
        if(p != NULL) {
            len = 0;
            len = p - start;
            if(len > 0) {
                strncat(tmp, start, len);
            }
            strncat(tmp, new_sub, strlen(new_sub));
            start = p + strlen(sub);
        }
        else {
            strcat(tmp, start);
            break;
        }
    } while(*start != '\0');

    char *buf = (char *)malloc(strlen(tmp) + 1);
    strcpy(buf, tmp);
    *dst = buf;

    return 0;
}

void freeBuf(char *buf) {
    free(buf);
    buf = NULL;
}

void freeBuf2(char **buf) {
    char *tmp = *buf;
    if(tmp != NULL) {
        free(tmp);
    }
    *buf = NULL;
}

void work5_heima() {
    char *p = "abcd11111abcd2222abcdqqqqq";
    char *buf = NULL;  // 在replace_heima函数中分配空间
    int ret = 0;
    char sub[] = "abcd";
    char new_sub[] = "f";
    ret = replacesubstr_heima(p, &buf, sub, new_sub);
    if(ret != 0) {
        printf("replacesubstr err: %d\r\n", ret);
        return;
    }
    printf("p = %s\r\n", p);
    printf("buf = %s\r\n", buf);
//    if(buf != NULL) {
//        free(buf);
//        buf = NULL;
//    }
//    freeBuf(buf);
    freeBuf2(&buf);
    if(buf != NULL) {
        printf("buf != NULL\r\n");
        free(buf);
    }
}

int spitString_heima(const char *str, char c, char buf[10][30], int *count) {

    if(str == NULL || buf == NULL || count == NULL) {
        return -1;
    }

    const char *start = str;
    char *p = NULL;
    int i = 0;
    do {
        p = strchr(start, c);
        if(p != NULL) {
            int len = p - start;
            strncpy(buf[i], start, len);
            // 结束符
            buf[i][len] = '\0';
            i++;
            // 重新设置起点位置
            start = p + 2;
        }
        else {
            break;
        }
    }while(*start != 0);

    if(i == 0) {
        return -2;
    }
    *count = i;
    return 0;
}



int work6_heima(void) {

    const char *p = "abcdef, acccd, aaaa, e3eeee, ssss,";
    char buf[10][30] = {0};
    int n = 0;
    int i = 0;
    int ret = 0;

    ret = spitString_heima(p, ',', buf, &n);
    if(ret != 0) {
        // printf("spitString err : %d\r\n", ret);
        return ret;
    }

    for(i = 0; i < n; i++) {
        printf("%s\r\n", buf[i]);
    }
    return 0;
}

char **getMem_heima(int n) {
    char **buf = NULL;  // char *buf[n]
    buf = (char **) malloc(n * sizeof(char *));
    if(buf == NULL) {
        return NULL;
    }
    int i;
    for(i = 0; i < n; i++) {
        buf[i] = (char *)malloc(30);
    }

    return buf;
}

int spitString_heima2(const char *str, char c, char **buf, int *count) {

    if(str == NULL || buf == NULL || count == NULL) {
        return -1;
    }

    const char *start = str;
    char *p = NULL;
    int i = 0;
    do {
        p = strchr(start, c);
        if(p != NULL) {
            int len = p - start;
            strncpy(buf[i], start, len);
            // 结束符
            buf[i][len] = '\0';
            i++;
            // 重新设置起点位置
            start = p + 2;
        }
        else {
            strcpy(buf[i], start);
            i++;
            break;
        }
    }while(*start != 0);

    if(i == 0) {
        return -2;
    }
    *count = i;
    return 0;
}

void freeBuf_heima(char **buf, int n) {
    int i;
    for(i = 0; i < n; i++) {
        free(buf[i]);
        buf[i] = NULL;
    }
    if(buf != NULL) {
        free(buf);
        buf = NULL;
    }
}

void freeBuf_heima1(char ***tmp, int n) {
    char **buf = *tmp;
    int i = 0;
    for(i = 0; i < n; i++) {
        free(buf[i]);
        buf[i] = NULL;
    }

    if(buf != NULL) {
        free(buf);
        buf = NULL;
    }

    *tmp = NULL;
}

void freeBuf_heima2(char ***buf, int n) {
    int i = 0;
    for(i = 0; i < n; i++) {
        free(*buf[i]);
        *buf[i] = NULL;
    }
    if(*buf != NULL) {
        free(*buf);
        buf = NULL;
    }
}


int work6_heima2(void) {
    const char *p = "abcdef, acccd, aaaa, e3eeee, ssss,";

    char **buf = NULL;
    int n = 0;
    int i = 0;
    int ret = 0;

    buf = getMem_heima(6);

    if(buf == NULL) {
        printf("buf = NULL\r\n");
        return -1;
    }

    ret = spitString_heima2(p, ',', buf, &n);
    if(ret != 0) {
        printf("spitString_heima2333 err %d\r\n", ret);
        return ret;
    }
    for(i = 0; i < n; i++) {
        printf("%s\r\n", buf[i]);
    }
//    freeBuf_heima(buf, n);
//    buf = NULL;
    freeBuf_heima2(&buf, n);
    if(buf != NULL) {
        printf("buf != NULL\r\n");
        free(buf);
        buf = NULL;
    }


#if 0
    for(i = 0; i < n; i++) {
        free(buf[i]);
        buf[i] = NULL;
    }
    if(buf != NULL) {
        free(buf);
        buf = NULL;
    }
#endif

    return 0;
}

char **getMem_Test6_heima(int n, int m) {

    if(n == 0 || m == 0) {
        return NULL;
    }

    char **buf = (char **) malloc(n * sizeof(char *));
    for(int i = 0; i < n; i++) {
        buf[i] = (char *)malloc(m * sizeof(char));
    }

    return buf;
}

int spitString_Test6_heima(const char *str, char c, char **buf, int *count) {

    if(str == NULL || buf == NULL || count == NULL) {
        return -1;
    }

    const char *start = str;
    char *p = NULL;

    int i = 0;
    do {
        p = strchr(start, c);
        if(p != NULL) {
            strncpy(buf[i], start, p - start);
            // 结束符
            buf[i][p - start] = '\0';
            i++;
            start = p + 2;
        }
        else {

            break;
        }


    } while(start != NULL);

    *count = i;

    return 0;
}

void freeBuf_test6_heima(char ***buf, int n) {
#if 0
    char **tmp = *buf;
    for(int i = 0; i < n; i++) {
        free(tmp[i]);
        tmp[i] = NULL;
    }
    if(tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }
    *buf = NULL;
#else
    for(int i = 0; i < n; i++) {
        free((*buf)[i]);
        (*buf)[i] = NULL;
    }
    if(*buf != NULL) {
        free(*buf);
        *buf = NULL;
    }

#endif
}

int Test6_heima(void) {
    const char *p = "abcdef, acccd, aaaa, e3eeee, ssss,";
    char **buf = NULL;
    int n = 6, m = 30;
    int ret = 0;
    int count = 0;
    buf = getMem_Test6_heima(n, m);

    if(buf == NULL) {
        printf("buf = NULL\r\n");
        return -1;
    }

    ret = spitString_Test6_heima(p, ',', buf, &count);

    if(ret != 0) {
        printf("spitString_Test6_heima ret = %d\r\n", ret);
        return ret;
    }

    for(int i = 0; i < count; i++) {
        printf("%s\r\n", buf[i]);
    }

    freeBuf_test6_heima(&buf, n);
    if(buf != NULL) {
        free(buf);
        buf = NULL;
    }

    return 0;
}

int main() {
    Test6_heima();
    printf("Hello, World!\n");
    return 0;
}



