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

void basic_operations_for_item_lists() {
    day7_03_Node *head = NULL;
    head = SList_Creat();   // 创建头结点
    SList_Print(head);
}

int main() {
    basic_operations_for_item_lists();
    printf("Hello, World!\n");
    return 0;
}
