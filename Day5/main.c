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

    strcpy((*p).name, "xiaozhang");
    (*p).age = 24;
    printf("%s, %d\r\n", (*p).name, (*p).age);
}

// 2、结构体相互赋值
typedef struct Teacher02 {
    // 定义结构体类型时不要直接给成员赋值
    // 因为结构体只是一个类型 还没有分配空间
    // 只有根据其类型定义变量时 才分配空间 有空间后才能赋值
    char name[50];
    int age;
} Teacher02;

void copyTeacher(Teacher02 to, Teacher02 from) {
    to = from;
    printf("[copyTeacher] %s %d\r\n", to.name, to.age);
}

void copyTeacher2(Teacher02 *to, Teacher02 *from) {
    *to = *from;
}


void fun(int to, int from) {
    to = from;
}

void structures_assign_values_to_each_other() {


    Teacher02 t1 = {"lily", 22};
    // 相同类型的两个结构体变量 可以相互赋值
    // 把t1成员变量内存的值拷贝给t2成员变量的内存
    // t1和t2没有关系
    Teacher02 t2 = t1;
    printf("%s, %d\r\n", t2.name, t2.age);

    int a = 10;
    int b = a;   // a的值给了b  a和b没有关系
    Teacher02 t3;
    memset(&t3, 0, sizeof(t3));
    copyTeacher2(&t3, &t1);  // t1拷贝给t3
    printf("[t3] %s %d\r\n", t3.name, t3.age);

    int c = 10;
    int d = 0;
    fun(d, c);  // c的值给b
    printf("d = %d\r\n", d);

}

// 3、结构体数组
typedef struct {
    char name[50];
    int age;
} Teacher03;

void struct_array() {
    Teacher03 a[3] = {
            {"a", 13},
            {"b", 14},
            {"c", 15},
    };

    // 静态
    Teacher03 a1[3] = {"a", 18, "b", 19, "c", 20};
    int i = 0;
    for(i = 0; i < 3; i++) {
        printf("%s %d\r\n", a1[i].name, a1[i].age);
    }

    // 动态
    int b[3] = {0};
    int *pb = (int *)malloc(3 * sizeof(int));
    free(pb);

    // Teacher03 p[3];
    Teacher03 *p = (Teacher03 *)malloc(3 * sizeof(Teacher03));
    if(p == NULL) {
        printf("p = NULL");
    }

    char buf[50];
    for(i = 0; i < 3; i++) {
        sprintf(buf, "name%d%d%d", i, i, i);
        strcpy(p[i].name, buf);
        p[i].age = 20 + i;
    }
    for(i = 0; i < 3; i++) {
        printf("%d , %s, %d\r\n", i+1, p[i].name, p[i].age);
    }
    if(p != NULL) {
        free(p);
        p = NULL;
    }
}

// 4、结构体套一级指针

typedef struct {
    char *name;
    int age;
} Teacher04;

void structure_nested_with_a_level_pointer() {
    char *name = NULL;
    name = (char *)malloc(30);
    strcpy(name, "lily");
    printf("name = %s\r\n", name);
    if(name != NULL) {
        free(name);
        name = NULL;
    }

    // 第一种情况
    Teacher04 t;
    t.name = (char *) malloc(30);
    strcpy(t.name, "lily");
    t.age = 22;
    printf("t.name = %s, t.age = %d\r\n", t.name, t.age);
    if(t.name != NULL) {
        free(t.name);
        t.name = NULL;
    }

    // 第二种情况
    Teacher04 *t2 = NULL;
    t2 = (Teacher04 *)malloc(sizeof(Teacher04));
    t2->name = (char *) malloc(30);
    strcpy(t2->name, "lily");
    t2->age = 22;
    printf("t2->name = %s, t2->age = %d\r\n", t2->name, t2->age);
    if(t2 != NULL) {
        if(t2->name != NULL) {
            free(t2->name);
            t2->name = NULL;
        }
        free(t2);
        t2 = NULL;
    }

    // 第三种情况
    Teacher04 *q = NULL;
    // Teacher q[3]
    char buf[30];
    q = (Teacher04 *)malloc(3 * sizeof(Teacher04));
    int i = 0;
    for(i = 0; i < 3; i++) {
        q[i].name = (char *) malloc(30);
        sprintf(buf, "name%d%d%d", i, i, i);
        strcpy(q[i].name, buf);
        q[i].age = 20 + 2 * i;
    }
    for(i = 0; i < 3; i++) {
        printf("q[%d]->name = %s q[%d]->age = %d\r\n", i, q[i].name, i, q[i].age);
    }
    if(q != NULL) {
        for(i = 0; i < 3; i++) {
            if(q[i].name != NULL) {
                free(q[i].name);
                q[i].name = NULL;
            }
        }
        free(q);
        q = NULL;
    }
}

// 5、结构体套二级指针
typedef struct {
    int age;
    char **stu;
} Teacher05;

void the_structure_has_two_level_pointers() {
    char **name = NULL;
    // char *name[3];
    int n = 3, i = 0;
    name = (char **)malloc(n * sizeof(char*));
    // char buf[30];
    for(i = 0; i < n; i++) {
        name[i] = (char *)malloc(30);
        strcpy(name[i], "lily");
    }
    for(i = 0; i < n; i++) {
        printf("name[%d] = %s\r\n", i, name[i]);
    }

    if(name != NULL) {
        for(i = 0; i < n; i++) {
            if(name[i] != NULL) {
                free(name[i]);
                name[i] = NULL;
            }
        }
        free(name);
        name = NULL;
    }

    // 第一种情况
    Teacher05 t1;
    t1.stu = (char **)malloc(3 * sizeof(char *));
    for(i = 0; i < 3; i++){
        t1.stu[i] = (char *)malloc(30);
    }
    for(i = 0; i < 3; i++) {
        char buf[30];
        sprintf(buf, "stu%d%d%d", i, i, i);
        strcpy(t1.stu[i], buf);
    }
    for(i = 0; i < 3; i++) {
        printf("t1.stu[%d] = %s\r\n", i, t1.stu[i]);
    }
    if(t1.stu != NULL) {
        for(i = 0; i < 3; i++) {
            if(t1.stu[i] != NULL) {
                free(t1.stu[i]);
                t1.stu[i] = NULL;
            }
        }
        free(t1.stu);
        t1.stu = NULL;
    }

    // 第二种情况
    Teacher05 *t2 = NULL;
    t2 = (Teacher05 *)malloc(sizeof(Teacher05));
    t2->stu = (char **)malloc(3 * sizeof(char*));
    for(i = 0; i < 3; i++) {
        char buf[30];
        t2->stu[i] = (char *) malloc(30);
        sprintf(buf, "t2->stu%d%d%d", i, i, i);
        strcpy(t2->stu[i], buf);
    }
    for(i = 0; i < 3; i++) {
        printf("t2->stu[%d] = %s\r\n", i, t2->stu[i]);
    }
    if(t2 != NULL) {
        if(t2->stu != NULL) {
            for(i = 0; i < 3; i++) {
                if(t2->stu[i] != NULL) {
                    free(t2->stu[i]);
                    t2->stu[i] = NULL;
                }
            }
            t2->stu = NULL;
        }
        t2 = NULL;
    }

    // 第三种情况
    Teacher05 *t3 = NULL;
    t3 = (Teacher05 *)malloc(3 * sizeof(Teacher05));
    for(i = 0; i < 3; i++) {
        t3[i].stu = (char **)malloc(3 * sizeof(char *));
    }
    int j = 0;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            char buf[30];
            t3[i].stu[j] = (char *)malloc(30);
            sprintf(buf, "t3[%d].stu[%d]", i, j);
            strcpy(t3[i].stu[j], buf);
        }
    }

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            printf("t3[%d].stu[%d] = %s\r\n", i, j, t3[i].stu[j]);
        }
    }

    if(t3 != NULL) {
        for(i = 0; i < 3; i++) {
            if(t3[i].stu != NULL) {
                for(j = 0; j < 3; j++) {
                    if(t3[i].stu[j] != NULL) {
                        free(t3[i].stu[j]);
                        t3[i].stu[j] = NULL;
                    }
                }
                free(t3[i].stu);
                t3[i].stu = NULL;
            }
        }
        free(t3);
        t3 = NULL;
    }
}

// 5.1、结构体套二级指针强化
int creatTeacher(Teacher05 **q, int n, int m) {
    if(q == NULL || n <= 0 || m <= 0) {
        return -1;
    }
    Teacher05 *tmp = NULL;
    tmp = (Teacher05 *)malloc(n * sizeof(Teacher05));
    if(tmp == NULL) {
        return -2;
    }
    int i = 0, j = 0;
    for(i = 0; i < n; i++) {
        tmp[i].stu = (char **)malloc(m * sizeof(char *));
        if(tmp[i].stu == NULL) {
            return -3;
        }
    }
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            tmp[i].stu[j] = (char *)malloc(30);
            if(tmp[i].stu[j] == NULL) {
                return -4;
            }
        }
    }

    *q = tmp;
    return 0;
}

int writeStuData(Teacher05 **q, int n, int m) {
    if(q == NULL || n <= 0 || m <= 0) {
        return -1;
    }
    Teacher05 *tmp = *q;
    char buf[50];
    int i = 0, j = 0;

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            sprintf(buf, "tmp[%d].stu[%d]", i, j);
            strcpy(tmp[i].stu[j], buf);
        }
        tmp[i].age = 20 + i;
    }

    return 0;
}

int printfTeacher(Teacher05 *q, int n, int m) {
    if(q == NULL || n <= 0 || m <= 0) {
        return -1;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("q[%d].stu[%d] = %s\r\n", i, j, q[i].stu[j]);
        }
    }
    return 0;
}

int freeTeacher(Teacher05 **q, int n, int m) {
    if(q == NULL || n <= 0 || m <= 0) {
        return -1;
    }
    Teacher05 *tmp = *q;
    int i = 0, j = 0;
    if(tmp != NULL) {
        for(i = 0; i < n; i++) {
            if(tmp[i].stu != NULL) {
                for(j = 0; j < m; j++) {
                    if(tmp[i].stu[j] != NULL) {
                        free(tmp[i].stu[j]);
                        tmp[i].stu[j] = NULL;
                    }
                }
                free(tmp[i].stu);
                tmp[i].stu = NULL;
            }
        }
        free(tmp);
        tmp = NULL;
        *q = tmp;
    }

    return 0;
}

int sortTeacher(Teacher05 *p, int n) {

    if(p == NULL || n <= 0) {
        return -1;
    }
    Teacher05 tmp;
    int i = 0, j = 0;
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].age < p[j].age) {
                 tmp = p[i];
                 p[i] = p[j];
                 p[j] = tmp;
            }
        }
    }


    return 0;
}

void the_structure_is_reinforced_with_two_level_Pointers() {
    int ret = 0;
    Teacher05 *q = NULL;
    ret = creatTeacher(&q, 3, 3);
    if(ret != 0) {
        printf("creatTeacher fail code = %d\r\n", ret);
        return;
    }
    ret = writeStuData(&q, 3, 3);
    if(ret != 0) {
        printf("writeStuData fail code = %d\r\n", ret);
        return;
    }
    printf("after sort\r\n");
    ret = printfTeacher(q, 3, 3);
    if(ret != 0) {
        printf("printfTeacher fail code = %d\r\n", ret);
        return;
    }

    ret = sortTeacher(q, 3);

    printf("sort end\r\n");
    ret = printfTeacher(q, 3, 3);
    if(ret != 0) {
        printf("printfTeacher fail code = %d\r\n", ret);
        return;
    }
    ret = freeTeacher(&q, 3, 3);
    if(ret != 0) {
        printf("freeTeacher fail code = %d\r\n", ret);
        return;
    }

    if(q == NULL) {
        printf("q is NULL\r\n");
    }
}


// 06、结构体深拷贝和浅拷贝
typedef struct {
    char *name;
    int age;
} Teacher06;

// 结构体中嵌套指针 而且动态分配内存
// 同类型结构体变量赋值
// 不同结构体成员指针变量指向同一块内存
void structure_deep_copy_and_shallow_copy() {
    Teacher06 t1;
    t1.name = (char *)malloc(30);
    strcpy(t1.name, "lily");
    t1.age = 22;
    Teacher06 t2;
    t2 = t1;    // 属于浅拷贝
    // 人为增加内容 重新拷贝一次 属于深拷贝
    t2.name = (char *)malloc(30);
    strcpy(t2.name, t1.name);
    printf("t2.name = %s, t2.age = %d\r\n", t2.name, t2.age);

    if(t1.name != NULL) {
        free(t1.name);
        t1.name = NULL;
    }

    // 当浅拷贝时 释放两次内存 程序会崩
    if(t2.name != NULL) {
        free(t2.name);
        t2.name = NULL;
    }

 }

// 07、结构体的偏移量
// 结构体类型定义下来 内部的成员变量的内存布局已经确定
typedef struct {
    char name[64];
    int age;
    int id;
} Teacher07;

void the_offset_of_the_structure() {
    Teacher07 t1;
    Teacher07 *p = NULL;
    p = &t1;
    int n1 = (int)(&p->age) - (int)p;    // 相当于结构体首地址
    printf("n1 = %d\r\n", n1);
    int n2 = (int)&((Teacher07*)0)->age;   // 绝对0地址的偏移量
    printf("n2 = %d\r\n", n2);
}

// 08、内存对齐测试
void memory_alignment_test() {
    struct {
        double c;
        int a;
        short b;
    } A;

    /**
     *  c : 8 * 0 = 0
     *  a : 4 * 2 = 8
     *  b : 2 * 6 = 12
     *
     *  c c c c c c c c
     *  a a a a b b * *
     */
    printf("sizeof(A) = %d\r\n", sizeof(A));

    struct {
        int a;
        double c;
        short b;
    } A1;

    /**
     *  a : 4 * 0 = 0
     *  c : 8 * 1 = 8
     *  b : 2 * 8 = 16
     *
     *  a a a a * * * *
     *  c c c c c c c c
     *  b b * * * * * *
     */

    printf("sizeof(A1) = %d\r\n", sizeof(A1));
}

int main() {
    memory_alignment_test();
    printf("Hello, World!\n");
    return 0;
}
