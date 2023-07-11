#include <stdio.h>
#include "stdlib.h"
#include <string.h>

// 1 一维数组
void one_dimensional_array(void) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // sizeof()测变量所占的内存空间（变量所对应类型的空间）
    // int b[];  // 定义时必须初始化
    int a1[100] = {1, 2, 3, 4};    // 没有赋值的都为0

    int n = 0;
    int i = 0;
    // sizeof(a) = 4 * 8 = 32   数组类型：由元素个数 和 元素类型决定   相当于8个int类型
    // sizeof(a[0])  首元素大小  每个元素4个字节
    // 局限性：如果当时定义数组时[]内写的是100 则求出的n就为100
    n = sizeof(a) / sizeof(a[0]);    // n = 8;

    for(i = 0; i < n; i++) {
        // *(a + i) : a + i  代表第i个元素地址  *(a + i) 指针指向的内存(取值)
        // [] 与 * 等价 都是取指针指向的内存区域
        // printf("%d ", a[i]);
        printf("%d ", *(a + i));
    }
    printf("\r\n");

    // 数组类型
    // a代表首元素地址  &a代表数组首地址
    // 两个地址是一样的 但是步长不一样
    printf("a : %d, a+1 : %d\r\n", a, a+1);  // 加4个字节
    printf("&a : %d, &a+1 : %d\r\n", &a, &a+1);   // 加32个字节

    // 数组类型由元素个数和元素类型决定
    // 通过typedef定义一个数组类型
    // 有typedef是类型 没有就是变量
    typedef int A[8];  // 代表是一个数组类型 他是一个类型 不是一个变量
    // typedef int (A)[8]; // 与上面等价

    A b;   // 等价于int b[8] 删掉了typedef b被替换到了A的位置

    for(i = 0; i < 8; i++) {
        b[i] = 2 * i + 1;
    }
    for(i = 0; i < 8; i++) {
        // printf("%d ", b[i]);    // 与下面写法等价
        printf("%d ", *(b + i));
    }
    printf("\r\n");

    printf("b: %d, b+1: %d\r\n", b, b+1);
    printf("&b: %d, &b+1: %d\r\n", &b, &b+1);

}

// 2 数组指针
void array_pointer(void) {
    // 数组指针与指针数组的区别
    // 指针数组 它是数组 每个元素都是指针 []比*优先级高
    char *a1[] = {"aaaaaaaa", "bbbbbbbbbbbb", "cccccccccccccc"};

    // 数组指针 它是指针 指向一个数组的指针
    // 数组指针 指向一维数组的整个数组 而不是首元素地址
    // 定义数组变量指针

    int i = 0;
    int a[10] = {0};
    int a2[10] = {0};
    int a3[10] = {0};
    // 1 先定义数组类型 根据类型定义指针变量
    typedef int A[10];   // A数组类型 [10]代表步长
    A *p = NULL;   // p就是一个数组指针类型变量
    // p = a;   // a代表首元素地址， a 和 &a 一样 最终也是当做&a处理 但是有一个警告
    p = &a;    // &a代表整个数组的首地址
    // 数组有多长 +1就能跳多长
    printf("p : %d, p+1 : %d\r\n", p, p+1);

    for(i = 0; i < 10; i++) {
        // a[i] = i + 1;
        // 间接赋值
        // p = &a
        // *p = *&a -> a
        (*p)[i] = i + 1;
    }

    for(i = 0; i < 10; i++) {
        printf("%d ", (*p)[i]);
    }
    printf("\r\n");

    // 2 先定义数组指针类型 根据类型定义变量 和指针数组写法很类似 只是多了()
    // ()和[] 的优先级一样 从左往右 ()里面有指针 它是一个指针
    // 后面有[] 表明是指向数组的指针 它有typedef 所以它是一个数组指针类型
    typedef int (*P)[10];
    P q = NULL;    // 数组指针变量
    q = &a2;
    for(i = 0; i < 10; i++) {
        (*q)[i] = 2 * i + 1;
    }
    for(i = 0; i < 10; i++) {
        printf("%d ", (*q)[i]);
    }
    printf("\r\n");


    // 3 直接定义数组指针变量
    // 和指针数组写法很类似 多了() ()和[]优先级一样 从左往右
    // ()有指针 它是一个指针 指向数组的指针 没有typedef 所以它是一个数组指针变量
    int (*qq)[10]; // qq数组指针变量
    qq = &a3;   // qq指向a3数组
    for(i = 0; i < 10; i++) {
        (*qq)[i] = 3 * i + 1;
    }
    for(i = 0; i < 10; i++) {
        printf("%d ", (*qq)[i]);
    }
    printf("\r\n");
}

// 3 二维数组的使用
void printA(int *a, int n) {
    int i = 0;
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\r\n");
}

// 数组做形参都会退化为指针 指针步长不一定一样
void printArray(int a[3][4]) {
    int i = 0, j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\r\n");
    }
}
// a + 1是一行 4 * 4 = 16个字节
void printArray1(int a[][4]) {
    int i = 0, j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\r\n");
    }
}

// 指针步长不一样 a+1是4个字节
void printArray2(int **a) {
    int i = 0, j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\r\n");
    }
}

// 数组指针 传进来的是首行首地址
void printArray3(int (*a)[4]) {
    int i = 0, j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\r\n");
    }
}

// 数组指针类型
typedef int (*PP)[4];
void printArray4(PP a) {
    int i = 0, j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\r\n");
    }
}

void the_use_of_two_dimensional_arrays(void) {
    int a1[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
    };
    int a2[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int a3[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int i = 0, j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", a3[i][j]);
        }
        printf("\r\n");
    }
    // +16
    // 二维数组数组名代表第0行的首地址(区别于第0行首元素的地址 虽然值一样)
    // 但是步长不一样
    printf("a3 : %d, a3+1 : %d\r\n", a3, a3+1);
    // 第0行首元素地址
    printf("%d, %d\r\n", *(a3+0), *(a3+1));
    printf("%d, %d\r\n", *(a3+0), *(a3+0)+1);
    printf("%d, %d\r\n", a3[0], a3[1]);
    printf("%d, %d\r\n", a3[0], a3[0]+1);

    int a[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // a : 代表第0行首地址
    // a + i  ->  &a[i] : 代表第i行首地址
    // *(a + i) -> a[i] : 代表第i行首元素地址
    // *(a + i) + j  ->  &a[i][j] : 第i行第j列元素的地址
    // *(*(a + i) + j)  ->  a[i][j] : 第i行第j列的元素的值
    // 二维数组数组名：第0行地址
    // a + i : 第i行首地址
    // 想要把首地址转化为首元素地址 加*
    // 想要得到某个元素地址 加偏移量： *(a+i)+0  *(a+i)+1  *(a+i)+j  ->  &a[i][0]  &a[i][1]  &a[i][j]
    // 要想得到某个元素的值 是在这个元素的地址基础上加*
    // *(*(a+i)+j)  -> *(&a[i][j])  ->  a[i][j]


    // 内存是线性存储的（不存在多维数组）
    int A[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("n = %d\r\n", sizeof(A));
    printA((int *)A, sizeof(A) / sizeof(a[0][0]));

    // 数组指针
    int A1[][10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // 3个A[4]的一维数组
    // 定义一个数组指针 步长要为4 跳一个要跳一行
    int (*p)[10] = NULL;
    // 指向二维数组的整个数组首地址
    // p = &a;
    // 第0行的首地址  等价于二维数组名
    p = A1;
    printf("p : %d, p+1 : %d\r\n", p, p+1);  // 跳了 4 * 10 = 40个
    int n = sizeof(A1)/sizeof(A1[0]);
    int nj = sizeof(A1[0])/sizeof(A1[0][0]);
    for(i = 0; i < n; i++) {
        for(j = 0; j < nj; j++) {
            printf("%d ", p[i][j]);
        }
        printf("\r\n");
    }

    int t[10];
    // 测一维数组长度：sizeof() 首行首元素地址
    printf("sizeof(t) = %d, sizeof(&t) = %d\r\n", sizeof(t), sizeof(&t));
    int tt[2][10];
    printf("sizeof(tt[0]) = %d, sizeof(&tt[0]) = %d\r\n", sizeof(tt[0]), sizeof(&tt[0]));
    printf("sizeof(*(tt+0)) = %d, sizeof(tt+0) = %d\r\n", sizeof(*(tt+0)), sizeof(tt+0));

    printf("tt[0] = %d, *(tt+0) = %d\r\n", tt[0], *(tt+0));

    // 二维数组做为函数参数
    // 定义数组指针类型 再定义变量
    typedef int(*P)[10];
    P p1 = tt;


    int a53[][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printArray4(a53);
}


void work1() {
    /**
     *  指针数组是一个数组 数组里的每一个元素都是指针
     *  数组指针是一个指针 指向数组的指针
     *  内存没有所谓的多维数组 只有一维数组
     *  数组名的本质是数组指针 就是数组的首地址 指向数组的指针
     * */
}

void work2() {
    int a[10];
    // 1 先定义数组类型 再根据类型定义指针变量
    typedef int A1[10];
    A1 *aa = &a;
    // 2 先定义数组指针类型 根据类型定义变量
    typedef int (*A2)[10];
    A2 aa2 = &a;
    // 3 直接定义数组指针变量
    int (*aa3)[10];
    aa3 = &a;

    printf("aa = %d, aa2 = %d, aa3 = %d\r\n", aa, aa2, aa3);
}

void work3() {
    int a[10];
    int b[5][10];
    int (*p)[10];
    p = &a;   // 为何加&
    p = b;    // 为何不加&

    /**
     *  p = &a;
     *  这行代码将指针'p'指向了数组'a' 因为'a'是一个一维数组 其类型是'int [10]'
     *  所以需要使用'&'算数运算符获取'a'数组的地址 这样指针'p'就指向了数组'a'的首地址
     *  p = b;
     *  这行代码将指针'p'指向了数组'b'的首行（第一个一维数组） 在这种情况下 因为数组'b'是
     *  一个二维数组 它的类型是'int[5][10]' 所以不需要使用'&'运算符 直接使用数组名'b'就
     *  可以表示二维数组的首地址
     *  总结起来 当将指针指向一个一维数组时 需要使用'&'运算符获取数组的地址 而当将指针指向
     *  一个二维数组时候 直接使用数组名就可以表示二维数组的首地址 这是因为在C语言中 二维数组
     *  名会被隐式转换成指向其首行的地址
     */
}

void work4() {
    int a[3][5] = {0};
    /**
     *  a -> a+0         代表a数组的第0行首地址
     *  a + i            代表a数组的第i行首地址
     *  *(a+i) -> a[i]   代表a数组的第i行元素的首地址
     *  *(a+i)+j -> &a[i][j]      代表a数组的第i行第j列元素的地址
     *  *(*(a+i)+j) -> a[i][j]    代表a数组的第i行第j列元素的值
     */
}

void work5() {
    // 如何在栈上开辟一个二维数组
    int arr1[3][4];
    int i = 0, j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            arr1[i][j] = i * 4 + j;
        }
    }
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("a[%d][%d] = %d\r\n", i, j, arr1[i][j]);
        }
    }
    // 如何在堆上开辟一个二维数组
    int **arr2 = (int **)malloc(3 * sizeof(int *));
    for(i = 0; i < 3; i++) {
        arr2[i] = (int *)malloc(4 * sizeof(int));
    }
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            arr2[i][j] = i * 4 + j;
        }
    }
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("a[%d][%d] = %d\r\n", i, j, arr2[i][j]);
        }
    }

    if(arr2 != NULL) {
        for(i = 0; i < 3; i++) {
            if(arr2[i] != NULL) {
                free(arr2[i]);
                arr2[i] = NULL;
            }
        }
        free(arr2);
        arr2 = NULL;
    }
}

void work6() {
    /**
     *  int main(int argc, char *argv[]);
     *  argc代表系统传入主函数的参数的格数
     *  argv是一个指针数组 代表传入进主函数的参数的数组
     */
}

int work7_searchKeyTable(const char *table[], const int size, const char *key, int *pos) {
    if(table == NULL || size <= 0 || key == NULL || pos == NULL) {
        return -1;
    }
    int i = 0;

    for(i = 0; i < size; i++) {
        if(strcmp(table[i], key) == 0) {
            *pos = i + 1;
            return 0;
        }

    }
    *pos = -1;
    printf("the key is not found\r\n");
    return -2;
}

void work7() {
    // 找到数组中指定字符串的位置
    const char *keywords[] = {
    "while",
    "case",
    "static",
    "do"
    };

    int keywords_n = sizeof(keywords)/ sizeof(keywords[0]);
    int pos = 0;
    int ret = work7_searchKeyTable(keywords, keywords_n, "while", &pos);

    if(ret == 0) {
        printf("pos = %d\r\n", pos);
    }
    else {
        printf("ret err code = %d\r\n", ret);
    }
}


// 将字符串数组进行排序
int sort(char **array1, int num1, char (*array2)[30], int num2, char ***myp3, int *num3) {

    if(array1 == NULL || num1 <= 0 || array2 == NULL || num2 <= 0 || myp3 == NULL || num3 == NULL) {
        return -1;
    }

    int len = num1 + num2;
    int i = 0, j = 0;
    char **buf = (char **)malloc(len * sizeof(char *));
    for(i = 0; i < len; i++) {
        buf[i] = (char *) malloc(30 * sizeof(char));
    }

    for(i = 0; i < len; i++) {
        if(i < 3) {
            strcpy(buf[i], array1[i]);
        }
        else {
            strcpy(buf[i], array2[i - 3]);
        }
    }

    for(i = 0; i < len; i++) {
        for(j = i + 1; j < len; j++) {
            if(strcmp(buf[i], buf[j]) > 0) {
                char *tmp = buf[i];
                buf[i] = buf[j];
                buf[j] = tmp;
            }
        }
    }
    *myp3 = buf;
    *num3 = len;
    return 0;
}

void work8() {
    int ret = 0;
    char *p1[] = {"aa", "ccccccc", "bbbbbb"};
    char buf2[10][30] = {"111111", "3333333", "222222"};
    char **p3 = NULL;
    int len1, len2, len3 = 0;
    int i = 0;
    len1 = sizeof(p1) / sizeof(*p1);
    len2 = 3;

    ret = sort(p1, len1, buf2, len2, &p3, &len3);

    if(ret == 0) {
        for(i = 0; i < len3; i++) {
            printf("p3[%d] = %s\r\n", i, p3[i]);
        }
    }
    else {
        printf("ret err code = %d\r\n", ret);
    }

    if(p3 != NULL) {
        for(i = 0; i < len3; i++) {
            if(p3[i] != NULL) {
                free(p3[i]);
                p3[i] = NULL;
            }
        }
        free(p3);
        p3 = NULL;
    }

}


// argc: 传参数的个数（包含可执行程序）
// argv: 指针数组 指向输入的参数
int main(int argc, char *argv[]) {
    work8();
    printf("Hello, World!\n");
    printf("argc = %d\r\n", argc);
    for(int i = 0; i < argc; i++) {
        printf("%s\r\n", argv[i]);
    }
    return 0;
}
