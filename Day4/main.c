#include <stdio.h>

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


}

// argc: 传参数的个数（包含可执行程序）
// argv: 指针数组 指向输入的参数
int main(int argc, char *argv[]) {
    work2();
    printf("Hello, World!\n");
    printf("argc = %d\r\n", argc);
    for(int i = 0; i < argc; i++) {
        printf("%s\r\n", argv[i]);
    }
    return 0;
}
