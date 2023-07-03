#include <stdio.h>

// 1 一维数组
void  one_dimensional_array(void) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // sizeof()测变量所占的内存空间（变量所对应类型的空间）
    // int b[];  // 定义时必须初始化
    int a1[100] = {1, 2, 3, 4};

    int n = 0;
    int i = 0;
    // sizeof(a) = 4 * 8 = 32   数组类型：由元素个数 和 元素类型组成   相当于8个int类型
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

int main() {
    one_dimensional_array();
    printf("Hello, World!\n");
    return 0;
}
