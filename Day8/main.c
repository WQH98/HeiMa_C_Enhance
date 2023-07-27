#include <stdio.h>
#include <stdlib.h>

// 01、递归的使用
void fun1_01(int a) {
    if(a == 1) {
        printf("a = %d\r\n", a);
        return;
    }
    fun1_01(a - 1);
    printf("a == %d\r\n", a);
}

int fun2_01(int a) {
    if(a == 100) {
        return a;
    }
    return a + fun2_01(a + 1);
}

void the_use_of_recursion() {
    fun1_01(3);
    int i = 0;
    int n = 100;
    int sum = 0;
    for(i = 0; i <= n; i++) {
        sum += i;
    }
    printf("sum = %d\r\n", sum);
    printf("fun2_01 = %d\r\n", fun2_01(1));
}

int main() {
    the_use_of_recursion();
    printf("Hello, World!\n");
    return 0;
}
