#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  1、结构体类型定义
 *  2、结构体变量定义
 *  3、结构体变量的初始化
 *  4、typedef改类型名
 *  5、点运算符和指针法操作结构体
 *  6、结构体也是一种数据类型 是一种复合类型或自定义类型
 */

// 1、结构体基本操作
void structure_basic_operations() {
    // 1、结构体类型定义
    // struct 关键字
    // struct Teacher合在一起才是类型
    // {}后面有分号
    struct Teacher {
        char name[50];
        int age;
    };

    // 2、结构体变量定义
    // 1 先定义类型 再定义变量
    struct Teacher t1; // 定义在函数外面是全局变量 函数里面是局部变量
    // 2 定义类型同时定义变量
    struct Teacher1 {
        char name[50];
        int age;
    }t3, t4 = {"TOM", 66};
    struct {
        char name[50];
        int age;
    }t5, t6;

    // 3、结构体变量的初始化
    // 定义变量时直接初始化 通过{}
    struct Teacher t7 = {"lily", 18};

    printf("%s, %d\r\n", t7.name, t7.age);

    // 4、typedef改类型名
    typedef struct Teacher3 {
        char name[50];
        int age;
    } Teacher3;
    struct Teacher3 t8;
    Teacher3 t9;

    // 5、点运算符和指针法操作结构体
    strcpy(t1.name, "xiaoming");
    t1.age = 22;
    printf("%s, %d\r\n", t1.name, t1.age);

    // 指针没有指向空间 指针的成员变量就不能赋值
    // 结构体指针变量 没有指向空间 不能给成员赋值
    struct Teacher *p = NULL;
    p = &t1;
    strcpy(p->name, "xiaojiang");
    p->age = 23;
    printf("%s, %d\r\n", p->name, p->age);

}

int main() {
    structure_basic_operations();
    printf("Hello, World!\n");
    return 0;
}
