#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 01 ��ҵ
char *get_mem(int size) {
    char *p = NULL;
    p = (char *) malloc(size);
    return p;
}

void HomeWork() {
    char buf[100];
    int a = 10;
    int *p = NULL;
    p = &a;
    *p = 20;

    char *mp = get_mem(100);
    strcpy(mp, "abcdefg");
    if(mp != NULL) {
        printf("before = %d\r\n", mp);
        free(mp);  // ����ϵͳ mpԭ��ָ����ڴ���Ա�����ʹ����
        printf("after = %d\r\n", mp);
        // �ͷ��� mp����Ұָ�� ���Ǳ���֮ǰ�ĵ�ַ ��ø�ֵΪNULL
        mp = NULL;
    }
}

// 02 ָ���ָ����ڴ����������ͬ�ĸ���
void APointerAndAPointedBlockOfMemoryAreTwoDifferentConcepts() {
    char *p = NULL;
    char buf[] = "abcdef";
    printf("before p = %d\r\n", p);
    // �ı�ָ�������ֵ
    p = buf;
    printf("after p = %d\r\n", p);
    // ָ�������ָ��ָ����ڴ���������ȫ��ͬ�ĸ���
    p = p + 1; // �ı���ָ�������ֵ �ı���ָ���ָ��
    printf("p++ = %d\r\n", p);
    printf("buf = %s\r\n", buf);
    printf("*p = %s\r\n", p);
    // �ı�ָ��ָ����ڴ� ������Ӱ�쵽ָ���ֵ
    buf[1] = '1';
    printf("�ı�ָ��ָ����ڴ� ������Ӱ�쵽ָ���ֵ\r\n");
    printf("after p = %d\r\n", p);
    printf("buf = %s\r\n", buf);

    *p = 'm';
    printf("after p = %d\r\n", p);
    printf("buf = %s\r\n", buf);

    // д�ڴ�ʱ һ��Ҫȷ���ڴ��д
    char *buf2 = "abcdefg";  // �����ֳ����� �ڴ治���޸�
    // buf2[2] = '1';  // �޸Ļᵼ�³�������ʱ�����

    char buf3[] = "abcdefg"; // �´����ջ��һ�� ջ�����ڴ�����޸�
    buf3[1] = '1'; // �����޸��ǿ��Ե�

    // ��p3ָ����ڴ����򿽱�����
    // char *p3 = NULL;
    // strcpy(p3, "1111");  // ���������Ǵ���� p3û�о����ָ���ڴ�
}

// 03 ���ϸı�ָ��ָ��
void KeepChangingThePointer() {
    char *p = NULL;
    char *q = NULL;

    char buf[100] = "abcdefg";
    p = &buf[0];
    printf("p = %d %c\r\n", p, *p);

    p = &buf[1];
    printf("p = %d %c\r\n", p, *p);

    for(int i = 0; i < strlen(buf); i++) {
        p = &buf[i]; // p = buf + i
        printf("p = %d %c\r\n", p, *p);
    }

    q = (char *)malloc(100);
    if(q == NULL) {
        printf("malloc err\r\n");
    }
    strcpy(q, "hijklmn");
    for(int i = 0; i < strlen(q); i++) {
        p = q + i;
        printf("%c ", *p);
    }
    printf("\r\n");
}

// 04 ͨ��ָ���Ӹ�ֵ
int get_a() {
    int a = 10;
    return a;
}

void get_a2(int b) {
    b = 22;
}

void get_a3(int *b) {
    *b = 22;  // ͨ��*�Ų����ڴ�
}

void get_a4(int *a1, int *a2, int *a3, int *a4) {
    *a1 = 1;
    *a2 = 2;
    *a3 = 3;
    *a4 = 4;
}

void fun2(int *p) {
    p = (int *)0x3344;
    printf("p = %p\r\n", p);
}

void fun3(int **p) {
    *p = (int *)0x5566;
    printf("*p = %p\r\n", *p);
}

void IndirectAssignmentThroughAPointer() {
    // ��Ӹ�ֵ������1 ��2������ һ����ͨ���� һ��ָ�����
    int a = 100;
    int *p = NULL;
    // ������ϵ ָ��ָ��˭ �Ͱ�˭�ĵ�ַ��ֵ��ָ��
    p = &a;
    // ͨ��*�����ڴ�
    *p = 22;
    // ͨ��ָ���Ӹ�ֵ
    // 1 ��������
    // 2 ������ϵ
    // 3 ͨ��*�����ڴ�

    int b = get_a();
    printf("b = %d\r\n", b);

    get_a2(b);
    printf("b = %d\r\n", b);

    // �����ͨ���βθı�ʵ�ε��ڴ����ݣ�ֵ�� �����ַ���� ʹ��ʵ�κ��β�
    get_a3(&b); // �ں�������ʱ ������ϵ
    printf("b = %d\r\n", b);

    int a1, a2, a3, a4;
    get_a4(&a1, &a2, &a3, &a4);
    printf("a1 = %d a2 = %d a3 = %d a4 = %d\r\n", a1, a2, a3, a4);

    // һ������ Ӧ�ö���һ��ʲô���͵�ָ�뱣�����ĵ�ַ
    // ��ԭ�����ͻ����ϼ�һ��*
    // cԭ��û��* ����c�ĵ�ַҪ��һ��*
    int c = 10;
    int *p1 = &c;
    // p1ԭ����һ��* ����p1�ĵ�ַҪ������*
    int **q1 = &p;
    // t������10��* ����t�ĵ�ַҪ��11��*
    int **********t = NULL;
    int ***********t2 = &t;

    int *p2 = (int *)0x1122;
    printf("p2 = %p\r\n", p);
    fun2(p2);
    printf("p2 = %p\r\n", p);
    fun3(&p2);
    printf("p2 = %p\r\n", p);
}

// 05 ָ�������������������
void fun4(char *p) {
    // ��pָ����ڴ����򿽱�
    strcpy(p, "abcdefg");
}

void fun5(char *p) {
    // ����ϰ�� ���ж�pΪ��Ϊ��
    if(p == NULL) {
        printf("err! p = NULL\r\n");
        return;
    }

    // ��pָ����ڴ����򿽱�
    strcpy(p, "abcdefg");
}

void fun6(char **p, int *len) {
    if(p == NULL) {
        return;
    }
    char *tmp = (char *) malloc(100);
    if(tmp == NULL) {
        return;
    }
    strcpy(tmp, "abcdefg");
    // ��Ӹ�ֵ
    *p = tmp;
    *len = strlen(tmp);

}

void PointersDoParameterInputOutputCharacteristics() {
    // ���� �������������ڴ�
    char buf[100] = {0};
    fun4(buf);
    printf("buf = %s\r\n", buf);

    // err ��δָ��������ڴ�дֵ
    char *str = NULL;
    fun5(str);

    // ����� �����ú��������ڴ� ��ַ����
    char *p = NULL;
    int len = 0;
    fun6(&p, &len);
    if(p != NULL) {
        printf("p = %s, len = %d\r\n", p, len);
    }
}

// 06 �ַ����ĳ�ʼ��
// C����û���ַ������� ��ͨ���ַ�������ģ���
// C�����ַ��� ���ַ�'\0'������0��β
void StringInitialization() {
    // ��ָ������ û��0������ �ж��ٸ�Ԫ�ؾ��ж೤
    char buf[] = {'a', 'b', 'c', 'd'};
    printf("buf = %s\r\n", buf); // ��ָ�����Ⱦʹ�ӡ û�н�β�Ľ����� ���ӡ����
    // ָ������ ����û�и�ֵ��Ԫ�� �Զ���0
    char buf1[100] = {'a', 'b', 'c', 'd'};
    printf("buf1 = %s\r\n", buf1);
    // ����Ԫ�ظ�ֵΪ0
    char buf2[100] = {0};
    // ����Խ��
    // char buf3[2] = {'1', '2', '3'};

    char buf4[50] = {'1', 'a', 'b', '0', '7'};
    printf("buf4 = %s\r\n", buf4);

    char buf5[50] = {'1', 'a', 'b', 0, '7'};
    printf("buf5 = %s\r\n", buf5);

    char buf6[50] = {'1', 'a', 'b', '\0', '7'};
    printf("buf6 = %s\r\n", buf6);

    // ��õ���ʹ���ַ�����ʼ��
    char buf7[] = "abcdef";
    // strlen�����ַ������� ����������0 �ַ�'\0'
    // sizeof�������鳤�� ��������0 �ַ�'\0'
    printf("strlen = %d, sizeof = %d\r\n", strlen(buf7), sizeof(buf7));

    char buf8[100] = "abcdef";
    printf("strlen = %d, sizeof = %d\r\n", strlen(buf8), sizeof(buf8));

    char buf9[] = "abcdefg";
    // �������鷽�� []��
    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", buf9[i]);
    }
    printf("\r\n");

    // �������鷽�� ָ�뷨
    // �������־���������Ԫ�صĵ�ַ
    char *p = NULL;
    p = buf9;
    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", p[i]);
    }
    printf("\r\n");

    // buf��p��ȫ�ȼ���
    // p++;
    // buf++;
    // bufֻ��һ������ �����޸�

    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", *(p + i));
    }
    printf("\r\n");

    for(int i = 0; i < strlen(buf9); i++) {
        printf("%c", *(buf9 + i));
    }
    printf("\r\n");
}

// 07 �ַ�������������ʵ��
void my_strcpy(char *dst, char *src) {
    int i = 0;
    for(i = 0; *(src + i) != '\0'; i++) {
        *(dst + i) = *(src + i);
    }
    *(dst + i) = '\0';
}

void my_strcpy2(char *dst, char *src) {
    while(*src != 0) {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

void my_strcpy3(char *dst, char *src) {
    while(*src != 0) {
        // *�ź�++���ȼ���ͬ ��ȡ���ҵ���
        // �����ټ�
        // ���൱��*dst = *src; dst++; src++;
        *dst++ = *src++;
    }
    *dst = '\0';
}

// ����ֵ���ɹ�Ϊ0 ʧ�ܷ��ط�0
// �ж��β�ָ���Ƿ�ΪNULL
// ��ò�Ҫֱ��ʹ���β�
// ����ʹ�ø����������βνӹ���
int my_strcpy4(char *dst, char *src) {
    if(dst == NULL || src == NULL) {
        return -1;
    }
    // *dst = *src;
    // dst++;
    // src++;
    // �ж�*dst�Ƿ�Ϊ0 Ϊ0����ѭ��
    while(*dst++ = *src++) {
        NULL;
    }
    return 0;
}

void StringCopyFunction() {
    char src[] = "abcdefg";
    char dst[100];
    int i = 0;
    for(i = 0; src[i] != 0; i++) {
        dst[i] = src[i];
    }
    // ��������
    dst[i] = 0;
    printf("dst = %s\r\n", dst);

    memset(dst, 0, 100);
    my_strcpy(dst, src);
    printf("my_strcpy dst = %s\r\n", dst);

    memset(dst, 0, 100);
    my_strcpy2(dst, src);
    printf("my_strcpy2 dst = %s\r\n", dst);

    memset(dst, 0, 100);
    my_strcpy3(dst, src);
    printf("my_strcpy3 dst = %s\r\n", dst);

    int ret = 0;
    memset(dst, 0, 100);
    ret = my_strcpy4(dst, src);
    if(ret != 0) {
        printf("my strcpy4 err:%d\r\n", ret);
    }
    printf("my_strcpy4 dst = %s\r\n", dst);

}

// strstr�е�while��do_whileģ��
void TheWhileAndDoWhileModelsInStrstr() {
    char *p = "11abcd11122abcd3333322abcd3333322qqqabcd";
    int n = 0;
    do{
        p = strstr(p, "abcd");
        if(p != NULL) {
            n++; //�ۼƵ�ַ
            // �������ò��ҵ����
            p = p + strlen("abcd");
        }
        else { // ���û��ƥ����ַ��� ������ѭ��
            break;
        }
    }while(*p != 0); // ���û�е��ַ�����β
    printf("n = %d\r\n", n);
}

void TheWhileAndDoWhileModelsInStrstr1() {
    char *p = "11abcd11122abcd3333322abcd3333322qqqabcd";
    int n = 0;

    while((p = strstr(p, "abcd")) != NULL) {
        // �ܽ����϶�������ƥ����Ӵ�
        // �����������λ��
        p += strlen("abcd");
        n++;
        if(*p == 0) {   //�����������
            break;
        }
    }

    printf("n = %d\r\n", n);
}

// ��ȷ����0 ���󷵻�-1
int my_strstr(char *p, int *n) {

    // ��������
    int i = 0;
    char *tmp = p;

    if(p == NULL) {
        return -1;
    }

    while((tmp = strstr(tmp, "abcd")) != NULL) {
        // �ܽ����϶�������ƥ����Ӵ�
        // �����������λ��
        tmp += strlen("abcd");
        i++;
        if(*tmp == 0) {   //�����������
            break;
        }
    }
    // ��Ӹ�ֵ
    *n = i;
    return 0;
}

void TheWhileAndDoWhileModelsInStrstr2() {
    char *p = "11abcd11122abcd3333322abcd3333322qqq";
    int n = 0;
    int ret = 0;

    ret = my_strstr(p, &n);
    if(ret != 0) {
        printf("err: not found\r\n");
    }

    printf("n = %d\r\n", n);
}

// �������� ������ͷ��ģ���м��ַ�������
int Two_endBlockingModel_fun(char *p, int *n) {
    if(p == NULL || n == NULL) {
        return -1;
    }

    int begin = 0;
    int end = (strlen(p) - 1);

    // �ȴ���߿�ʼ �����ǰ�ַ�Ϊ�� ����û������������
    while(isspace(p[begin]) && p[begin] != 0) {
        begin++;  // λ�ô��������ƶ�һλ
    }

    // �ٴ��ұ߿�ʼ �����ǰ�ַ�Ϊ�� ����û������������
    while(isspace(p[end]) && p[end] != 0) {
        end--;   // λ�ô��������ƶ�һλ
    }

    *n = end - begin + 1;
    return 0;
}

// �������� ������ͷ��ģ���о�����ַ���
int Two_endBlockingModel_fun2(char *p, char *buf) {
    int n = 0;

    if(p == NULL || buf == NULL) {
        return -1;
    }

    int begin = 0;
    int end = (strlen(p) - 1);

    // �ȴ���߿�ʼ �����ǰ�ַ�Ϊ�� ����û������������
    while(isspace(p[begin]) && p[begin] != 0) {
        begin++;  // λ�ô��������ƶ�һλ
    }

    // �ٴ��ұ߿�ʼ �����ǰ�ַ�Ϊ�� ����û������������
    while(isspace(p[end]) && p[end] != 0) {
        end--;   // λ�ô��������ƶ�һλ
    }

    n = end - begin + 1;

//    for(int i = 0; i < n; i++, begin++) {
//        buf[i] = p[begin];
//    }

    strncpy(buf, p+begin, n);

    buf[n] = 0;

    return 0;
}

int Two_endBlockingModel() {
    char *p = "      abcdeewrwerfg      ";
    int n = 0;
    int ret = 0;
    int ret2 = 0;
    char buf[100] = {0};

    ret = Two_endBlockingModel_fun(p, &n);
    ret2 = Two_endBlockingModel_fun2(p, buf);

    if(ret != 0) {
        return ret;
    }

    if(ret2 != 0) {
        return ret2;
    }

    printf("buf = %s\r\n", buf);
    printf("n = %d\r\n", n);

    return 0;
}

int main() {
    Two_endBlockingModel();
    printf("Hello, World!\n");
    return 0;
}
