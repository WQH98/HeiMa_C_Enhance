#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 01、结构体套结构体
typedef struct {
    int a;
    int b;
    char *p;
} day7_01_a;

// 结构体可以嵌套另外一个结构体的任何类型变量
// 结构体嵌套本结构体普通变量（不可以）
// 本结构体的类型大小无法确定 类型本质 固定大小内存块别名
// 结构体嵌套本结构体指针变量（可以）
// 指针变量的空间能确定 32位 4字节  64位 8字节
typedef struct day7_01_b{
    int a;
    day7_01_a tmp1;
    day7_01_a *tmp2;
    // day7_01_b tmp3;  // 不行
    struct day7_01_b *next; // 32位 4字节   64位 8字节
} day7_01_b;

// 02、静态链表的使用
typedef struct day7_02_a {
    int id;   // 数据域
    char name[32];
    struct day7_02_a *next;   // 指针域
} day7_02_a;

void the_use_of_static_linked_lists() {
    // 初始化3个结构体变量
    day7_02_a d1 = {1, "mike", NULL};
    day7_02_a d2 = {2, "lily", NULL};
    day7_02_a d3 = {3, "lilei", NULL};
    // 指针指向谁 就把谁的地址赋值给指针
    d1.next = &d2;    // d1的next指针指向d2
    d2.next = &d3;
    d3.next = NULL;   // 尾结点

    // 提供一个d1 把整个链表的内容获取到
    day7_02_a *p = &d1;
    while(p != NULL) {
        printf("id = %d, name = %s\r\n", p->id, p->name);
        // 结点往后移动一位
        p = p->next;
    }
}

// 03、单项列表的基本操作
/**
 *  (1) 建立带有头结点的单向链表
 *      编写函数SList_Creat 建立带有头结点的单向链表 循环创建结点 结点数据域中的数值从键盘输入
 *      以-1作为输入结束标志 链表的头结点地址由函数值返回
 *  (2) 顺序访问链表中各节点的数据域
 *      编写函数SList_Print 顺序输出单向链表各项数据域中的内容
 *  (3) 在单项列表中插入节点
 *      编写函数SList_NodeInset 功能 在值为x的结点前 插入值为y的结点 若值为x的结点不存在 则插在表尾
 *  (4) 删除单向链表中的节点
 *      编写函数SList_NodeDel 删除值为x的结点
 */

typedef struct day7_03_Node {
    int id;
    struct day7_03_Node *next;  // 指针域
} day7_03_Node;

// 创建头结点 链表的头结点地址由函数值返回
day7_03_Node *SList_Creat() {
    day7_03_Node *head = NULL;
    // 头结点作为标志 不存储有效数据
    head = (day7_03_Node *)malloc(sizeof(day7_03_Node));
    if(head == NULL) {
        return NULL;
    }
    head->id = -1;
    head->next = NULL;

    day7_03_Node *pCur = head;
    day7_03_Node *pNew = NULL;

    int data;
    while(1) {
        printf("please input data\r\n");
        scanf("%d", &data);
        // 输入-1 就退出
        if(data == -1) {
            break;
        }
        // 给新节点动态分配空间
        pNew = (day7_03_Node *)malloc(sizeof(day7_03_Node));
        if(pNew == NULL) {
            printf("pNew malloc failed, please input again\r\n");
            continue;
        }
        // 给pNew成员变量赋值
        pNew->id = data;
        pNew->next = NULL;
        // 链表建立关系
        // 当前结点的next指向pNew
        pCur->next = pNew;
        // pNew下一个结点指向NULL
        pNew->next = NULL;
        // 把pCur移动到pNew pCur指向pNew
        pCur = pNew;
    }

    return head;
}

// 链表的遍历
int SList_Print(day7_03_Node *head) {
    if(head == NULL) {
        return -1;
    }
    // 取出第一个结点（头结点的next）
    day7_03_Node *pCur = head->next;
    printf("head -> ");
    while(pCur != NULL) {
        printf("%d -> ", pCur->id);
        // 当前结点往下移动一位 pCur指向下一个
        pCur = pCur->next;
    }
    printf("NULL\r\n");
    return 0;
}

// 插入结点
// 在值为x的结点前 插入值为y的结点 若值为x的值不存在 则插在表尾
int SList_NodeInset(day7_03_Node *head, int x, int y) {
    if(head == NULL) {
        return 0;
    }
    day7_03_Node *pPre = head;
    day7_03_Node *pCur = head->next;

    while(pCur != NULL) {

        if(pCur->id == x) {

            break;
        }
        // pPre指向pCur位置
        pPre = pCur;
        // pCur指向下一个结点
        pCur = pCur->next;
    }

    // 2种情况
    // 1、找到匹配的结点 pCur为匹配结点 pPre为pCur上一个结点
    // 2、没找到匹配结点 pCur为空结点 pPer为最后一个结点
    // 给新结点动态分配空间
    day7_03_Node *pNew = (day7_03_Node *)malloc(sizeof(day7_03_Node));
    if(pNew == NULL) {
        return -2;
    }
    // 给pNew的成员变量赋值
    pNew->id = y;
    pNew->next = NULL;

    // 插入到指定位置
    pPre->next = pNew;   // pPre下一个指向pNwe
    pNew->next = pCur;   // pNew下一个指向pCur

    return 0;
}

// 删除第一个值为x的结点
int SList_NodeDel(day7_03_Node *head, int x) {
    if(head == NULL) {
        return -1;
    }

    day7_03_Node *pPre = head;
    day7_03_Node *pCur = head->next;
    // 标志位 0：没有找到 1：找到了
    int flag = 0;
    while(pCur->next != NULL) {
        // 找到了匹配结点
        if(pCur->id == x) {
            flag = 1;
            break;
        }

        pPre = pCur;
        pCur = pCur->next;
    }
    if(flag == 1) {
        // pPre的下一个结点指向pCur的下一个结点
        pPre->next = pCur->next;
        if(pCur != NULL) {
            free(pCur);
            pCur = NULL;
        }
    }
    if(0 == flag) {
        printf("don't find the value\r\n");
        return -2;
    }

    return 0;
}

// 清空链表 释放所有结点
int SList_NodeDsetroy(day7_03_Node *head) {
    if(head == NULL) {
        return -1;
    }
    int i = 0;
    day7_03_Node *tmp = NULL;
    while(head != NULL) {
        // 保存head的下一个结点
        tmp = head->next;
        free(head);
        head = NULL;
        // head指向tmp
        head = tmp;
        i++;
    }
    printf("i = %d\r\n", i);

    return 0;
}

void basic_operations_for_item_lists() {
    day7_03_Node *head = NULL;
    head = SList_Creat();   // 创建头结点
    SList_Print(head);
    SList_NodeInset(head, 5, 4);
    SList_Print(head);
    SList_NodeDel(head, 5);
    SList_Print(head);
    SList_NodeDsetroy(head);
    free(head);
    head = NULL;
}


// 04、函数指针
// 指针函数（()的优先级比*高 所以这是个函数 返回值是指针类型的函数）
int *fun_04() {
    int *p = (int *)malloc(sizeof(int));

    return p;
}

int fun2_04(int a) {
    printf("a ========= %d\r\n", a);
    return 0;
}

void function_pointer(void) {
    // 函数指针 它是指针 指向函数的指针
    // 定义函数指针变量有3种方式
    // 1、先定义函数类型 根据类型定义指针变量 （不常用的定义方式）
    // 有typedef是类型 没有就是变量
    typedef int FUN2_04(int a);   // fun2_04函数类型
    // 函数指针变量
    // 指针函数指向的变量有要求 返回值要int类型 参数是一个int类型
    FUN2_04 *p1 = NULL;
    p1 = fun2_04;  // p1指向fun2_04函数
    fun2_04(5); // 传统调用
    p1(6);    // 函数指针变量调用方式

    // 2、先定义函数指针变量 根据类型定义指针变量（常用）
    typedef int (*PFUN2_04)(int a);   // PFUN2_04 函数指针类型
    PFUN2_04 p2 = fun2_04;   // p2指向fun2_04函数
    p2(7);

    // 3、直接定义函数指针变量（常用）
    int (*p3)(int a) = fun2_04;
    p3(8);
    int (*p4)(int a);
    p4 = fun2_04;
    p4(9);
}

// 05、函数指针的应用
void add() {
    printf("add\r\n");
}
void minus() {
    printf("minus\r\n");
}
void multi() {
    printf("multi\r\n");
}
void divide() {
    printf("divide\r\n");
}
void myexit() {
    exit(0);
}

void application_of_function_pointers() {
#if 0
    char cmd[100];
    while(1) {
        printf("please enter cmd:");
        scanf("%s", cmd);
        if(strcmp(cmd, "add") == 0) {
            add();
        }
        else if(strcmp(cmd, "min") == 0) {
            minus();
        }
        else if(strcmp(cmd, "mul") == 0) {
            multi();
        }
        else if(strcmp(cmd, "div") == 0) {
            divide();
        }
        else if(strcmp(cmd, "exit") == 0) {
            myexit();
        }
    }
#endif

    void(*fun1_05)() = add;
    fun1_05();
    // 菜单越多 函数越多 这样写越简洁
    // 函数指针数组
    void (*fun2_05[5])() = {add, minus, multi, divide, myexit};
    // 指针数组
    char *buf[] = {"add", "min", "mul", "div", "exit"};

    char cmd[100];
    int i = 0;
    while(1) {
        printf("please enter cmd:");
        scanf("%s", cmd);
        for(i = 0; i < 5; i++) {
            if(strcmp(cmd, buf[i]) == 0) {
                fun2_05[i]();
                break;
            }
        }
    }
}

// 6、回调函数
int add_06(int a, int b) {
    return a + b;
}
int minus_06(int a, int b) {
    return a - b;
}
// 函数的参数是变量 函数指针也是变量
// 框架 固定变量
// 多态：多种形态 调用同一接口 但是不一样的表现
void fun1_06(int x, int y, int(*p)(int a, int b)) {
    printf("fun1_06\r\n");
    int a = p(x, y);   // 回调函数
    printf("a = %d\r\n", a);
}
typedef int(*P)(int a, int b);
void fun2_06(int x, int y, P p) {
    printf("fun1_06\r\n");
    int a = p(x, y);   // 回调函数
    printf("a = %d\r\n", a);
}
void callback_function() {
    fun1_06(1, 2, add_06);
    fun2_06(10, 5, minus_06);
}

/**
 *  work01
 *  struct teacher {
 *      int id;
 *      struct teacher t1;
 *  };
 *  这种结构体类型为什么能够编译过？
 *  编译不通过 结构体可以嵌套另外一个结构体的任何类型变量
 *  但是不能嵌套本结构体的普通变量 因为本结构体的类型大小无法确定（类型的本质是固定大小的内存块的别名）
 *  结构体可以嵌套本结构体指针变量 因为指针变量的空间能确定
 */


/**
 *  work02
 *  简述指针和链表的区别
 *  数组：一次性分配一块连续的内存区域
 *      优点：随机访问元素效率高
 *      缺点：(1) 需要分配一块连续的内存区域
 *           (2) 删除和插入某个元素的效率低
 *  链表：现实生活中的灯笼
 *      优点：(1) 不需要一块连续的内存区域
 *           (2) 删除和插入某个元素的效率高
 *      缺点：随机访问元素效率低
 */

/**
 *  work03
 *  把上面单向列表的基本操作重新敲一遍
 *  // 创建头结点 链表的头结点地址由函数返回
 *  SList *SListCreat();
 *  // 遍历节点
 *  // 顺序输出单向链表各项结点数据域中的内容
 *  int SListPrint(SList *pHead);
 *  // 在值为x的结点前 插入值为y的结点
 *  // 若值为x的结点不存在 则插在末尾
 *  int SListNodeInsert(SList *pHead, int x, int y);
 *  // 删除第一个值为x的结点
 *  int SListNodeDel(SList *pHead, int x);
 *  // 释放所有结点
 *  int SListDestroy(SList *pHead);
 */

typedef struct SList {
    int id;
    struct SList *next;
} SList;

SList *SListCreat() {
    SList *head = NULL;
    head = (SList *)malloc(sizeof(SList));
    head->id = -1;
    head->next = NULL;

    SList *pcur = head;
    SList *pnew = NULL;

    int data = 0;
    while(1) {
        printf("please enter the id: ");
        scanf("%d", &data);
        if(data == -1) {
            break;
        }
        pnew = (SList *)malloc(sizeof(SList));
        if(pnew == NULL) {
            printf("pnew malloc failed please enter again\r\n");
            continue;
        }
        pnew->id = data;
        pnew->next = NULL;
        pcur->next = pnew;
        pnew->next = NULL;
        pcur = pnew;
    }

    return head;
}

int SListPrint(SList *pHead) {
    if(pHead == NULL) {
        return -1;
    }

    SList *pcur = pHead->next;
    printf("pHead -> ");
    while(pcur != NULL) {
        printf("%d -> ", pcur->id);
        pcur = pcur->next;
    }
    printf("NULL\r\n");
    return 0;
}

int SListNodeInsert(SList *pHead, int x, int y) {

    if(pHead == NULL) {
        return -1;
    }

    SList *ppre = pHead;
    SList *pcur = NULL;
    pcur = ppre->next;
    while(pcur != NULL) {
        if(pcur->id == x) {
            break;
        }
        ppre = pcur;
        pcur = pcur->next;
    }
    SList *pnew = (SList *)malloc(sizeof(SList));
    if(pnew == NULL) {
        return -2;
    }
    pnew->id = y;
    pnew->next = NULL;

    ppre->next = pnew;
    pnew->next = pcur;

    return 0;
}

int SListNodeDel(SList *pHead, int x) {
    if(pHead == NULL) {
        return -1;
    }

    SList *ppre = pHead;
    SList *pcur = pHead->next;
    int flag = 0;
    while(pcur != NULL) {
        if(pcur->id == x) {
            flag = 1;
            break;
        }
        ppre = pcur;
        pcur = pcur->next;
    }
    if(flag == 1) {
        ppre->next = pcur->next;
        if(pcur != NULL) {
            free(pcur);
            pcur = NULL;
        }
    }
    else {
        printf("don't find the value in the list\r\n");
        return -2;
    }
    return 0;
}

int SListDestroy(SList *pHead) {
    if(pHead == NULL) {
        return -1;
    }
    int i = 0;
    SList *tmp = NULL;
    while(pHead != NULL) {
        tmp = pHead->next;
        if(pHead != NULL) {
            free(pHead);
            pHead = NULL;
            i++;
        }
        pHead = tmp;
    }
    printf("i = %d\r\n", i);
    return 0;
}

void work03() {
    SList *head = NULL;
    head = SListCreat();
    SListPrint(head);
    SListNodeInsert(head, 5, 4);
    SListPrint(head);
    SListNodeDel(head, 4);
    SListPrint(head);
    SListNodeDel(head, 4);
    SListPrint(head);
    SListNodeDel(head, 4);
    SListPrint(head);
    SListDestroy(head);
    head = NULL;
}

/**
 *  work04
 *  链表练习
 *  // 删除值为x的所有结点
 *  int SListNodeDelPro(SList *pHead, int x);
 *
 *  // 链表结点排序
 *  int SListNodeSort(SList *pHead);
 *  // 注意 排序 除了数据域要交换 next指针也需要交换
 *      if(pPre->id > pCur->id) {
 *          // 交换数字域
 *          tmp = *pCur;
 *          *pCur = *pPre;
 *          *pPre = *tmp;
 *
 *          // 交换指针域
 *          tmp.next = pCur->next;
 *          pCur->next = pPre->next;
 *          pPre->next = tmp.next;
 *      }
 *  // 假如原来链表是升序的 升序插入新结点
 *  // 不能插入结点后再升序 是升序插入新结点
 *  int SListNodeInsertPro(SList *pHead, int x);
 *  // 翻转列表的结点（不是排序 是翻转）
 *  int SListNodeReveres(SList *pHead);
 *
 *  创建头结点
 *  打印输出
 *  在4前面插入3
 *  打印输出
 *  删除第一个值为4的结点
 *  打印输出
 *  删除所有值为3的结点
 *  打印输出
 *  链表结点排序
 *  打印输出
 *  升序插入5
 *  打印输出
 *  翻转列表结点
 *  打印输出
 */

int SListNodeDelPro(SList *pHead, int x) {

    if(pHead == NULL) {
        return -1;
    }

    SList *ppre = pHead;
    SList *pcur = pHead->next;
    SList *tmp = NULL;

    while(pcur != NULL) {
        if(pcur->id == x) {
            ppre->next = pcur->next;
            if(pcur != NULL) {
                free(pcur);
                pcur = ppre->next;
            }
            continue;
        }
        ppre = pcur;
        pcur = pcur->next;
    }

    return 0;
}

int SListNodeSort(SList *pHead) {

    if(pHead == NULL) {
        return -1;
    }

    SList *ppre = pHead;
    SList *pcur = pHead->next;
    SList *end = NULL;

    while(ppre != end){
        while(pcur != end) {
            if(ppre->id > pcur->id) {
                SList tmp = *ppre;
                *ppre = *pcur;
                *pcur = tmp;

                tmp.next = pcur->next;
                pcur->next = ppre->next;
                ppre->next = tmp.next;
            }
            ppre = pcur;
            pcur = pcur->next;
        }
        end = ppre;
        ppre = pHead;
        pcur = pHead->next;
    }
    return 0;
}

int SListNodeInsertPro(SList *pHead, int x) {
    if(pHead == NULL) {
        return -1;
    }

    SList *pper = pHead;
    SList *pcur = pHead->next;
    SList *pnew = (SList *)malloc(sizeof(SList));
    pnew->id = x;
    pnew->next = NULL;

    if(x < pcur->id) {
        pper->next = pnew;
        pnew->next = pcur;
        return 0;
    }

    while(pper->next != NULL) {
        if(x > pper->id && x <= pcur->id) {
            pper->next = pnew;
            pnew->next = pcur;
            return 0;
        }
        pper = pcur;
        pcur = pcur->next;
    }
    pper->next = pnew;
    pnew->next = pcur;
    return 0;
}

int SListNodeInsertPro_Heima(SList *pHead, int x) {

    if(pHead == NULL) {
        return -1;
    }

    SList *ppre = pHead;
    SList *pcur = NULL;
    pcur = ppre->next;
    while(pcur != NULL) {
        if(pcur->id > x) {
            break;
        }
        ppre = pcur;
        pcur = pcur->next;
    }
    SList *pnew = (SList *)malloc(sizeof(SList));
    if(pnew == NULL) {
        return -2;
    }
    pnew->id = x;
    pnew->next = NULL;

    ppre->next = pnew;
    pnew->next = pcur;

    return 0;
}


int SListNodeSort_Heima(SList *pHead) {
    if(pHead == NULL) {
        return -1;
    }

    SList *ppre = NULL;
    SList *pcur = NULL;
    SList tmp;

    for(ppre = pHead->next; ppre->next != NULL; ppre = ppre->next) {
        for(pcur = ppre->next; pcur != NULL; pcur = pcur->next) {
            if(ppre->id > pcur->id) {
#if 1
                // 只交换数字域
                tmp.id = ppre->id;
                ppre->id = pcur->id;
                pcur->id = tmp.id;
#endif

#if 0
                // 交换数据域
                tmp = *ppre;
                *ppre = *pcur;
                *pcur = tmp;
                // 交换指针域
                tmp.next = pcur->next;
                pcur->next = ppre->next;
                ppre->next = tmp.next;
#endif
            }
        }
    }

}

int SListNodeReveres(SList *pHead) {
    if(pHead == NULL) {
        return -1;
    }

    SList *pper = pHead->next;
    SList *pcur = pper->next;
    SList *paft = pcur->next;

    pper->next = NULL;

    while(pcur != NULL) {

        pcur->next = NULL;
        pcur->next = pper;

        pper = pcur;
        pcur = paft;
        if(paft != NULL) {
            paft = paft->next;
        }
    }

    pHead->next = pper;

    return 0;
}

int SListNodeReveres_Heima(SList *pHead) {
    if(pHead == NULL) {
        return -1;
    }

    SList *pper = pHead->next;
    SList *pcur = pper->next;
    pper->next = NULL;
    SList *tmp = NULL;

    while(pcur != NULL) {
        tmp = pcur->next;
        pcur->next = pper;
        pper = pcur;
        pcur = tmp;
    }

    pHead->next = pper;

    return 0;
}

void work04() {
    SList *head = NULL;
    head = SListCreat();
    SListPrint(head);
    SListNodeInsert(head, 4, 3);
    SListPrint(head);
    SListNodeDel(head, 4);
    SListPrint(head);
    SListNodeDelPro(head, 3);
    SListPrint(head);
    SListNodeSort_Heima(head);
    SListPrint(head);
    SListNodeInsertPro_Heima(head, 9);
    SListPrint(head);
    SListNodeReveres_Heima(head);
    SListPrint(head);
    SListDestroy(head);
    head = NULL;
}

/**
 *  work05
 *  通过递归实现1+2+3+...+100的累加
 */

int add_05(int x) {
    if(x >= 100) {
        return 100;
    }
    return x + add_05(x+1);
}

void work05() {
    printf("add = %d\r\n", add_05(1));
}

int main() {
    setbuf(stdout,NULL);
    work04();
    printf("Hello, World!\n");
    return 0;
}
