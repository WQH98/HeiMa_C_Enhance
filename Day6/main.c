#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>

// 1 缓冲区验证
void buffer_verification() {
    char buf[] = "this is a test\r\n";
    FILE *fp = fopen("../test.txt", "w");
    // 此刻buf里面的值会写入缓冲区 而不是写入到文件中
    // 当程序结束 或文件关闭 或刷新缓冲区的时候才会从缓冲区写入到文件中
    fputs(buf, fp);
    fflush(fp);    // 刷新缓冲区
    fclose(fp);    // 文件关闭
}

// 输出文件路径验证
void output_path_verification() {
    char buf[1024];
    getcwd(buf, 1024);
    printf("%s\r\n", buf);
}

// 2 按照字符读写文件
void read_and_write_files_by_character() {
    fputc('a', stdout);    // stdout -> 屏幕  打印普通信息
    char ch;
    ch = fgetc(stdin);      // stdin -> 键盘
    printf("ch = %c\r\n", ch);
    fprintf(stderr, "%c", ch);      // stderr -> 屏幕  打印错误信息
    fputc(ch, stderr);

    FILE *fp = NULL;

    // 绝对路径
    // D:\\codes\\C_Pro\\CLion\\HeiMa_C_Enhance\\day6    windows
    // D:/codes/C_Pro/CLion/HeiMa_C_Enhance/day6    windows and linux都支持 建议'/'

    // 相对路径
    // ./ : 当前路径   ../ : 上一级路径
    // VS : 编译代码时 相对于项目工程(项目代码) 直接运行可执行程序（相对于程序的路径）
    fp = fopen("../test.txt", "r+");
    if(fp == NULL) {
        perror("fopen");
        return;
    }

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

    // 如果字符串太长了 使用下面的方式换行
    char *tmp = "sadasdasdadadsdada"\
                "adadadasdasdadsadad";
    printf("%s\r\n", tmp);

}

void my_fputc(char *path) {
    FILE *fp = NULL;
    // "w+" 表示读写方式打开 如果不存在 则创建 如果文件存在 清空内容 再写
    fp = fopen(path, "w+");
    if(fp == NULL) {
        ferror("my_fputs fopen");
        return;
    }

    // 写文件
    char buf[] = "this is a test for fputs";
    int i = 0;
    int n = strlen(buf);
    for(i = 0; i < n; i++) {
        // 返回值ch 是成功写入的字符
        char ch = fputc(buf[i], fp);
        printf("ch = %c\r\n", ch);
    }

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}


// fputc的使用
void use_of_fputc() {
    my_fputc("../test.txt");
}


void my_fgetc(char *path) {
    FILE *fp = NULL;
    // 读写方式打开 如果文件不存在 打开失败
    fp = fopen(path, "r+");

    if(fp == NULL) {
        perror("my_fgetc fopen");
        return;
    }

    char ch;
//    while((ch = fgetc(fp)) != EOF) {
//        printf("%c", ch);
//    }
//    printf("\r\n");

    // 如果文件没有结束
    while(!feof(fp)) {
        ch = fgetc(fp);
        printf("%c", ch);
    }
    printf("\r\n");

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}

// fgetc的使用
void use_of_fgetc() {
    my_fgetc("../test.txt");
}


// 3、按照行读写文件
void my_fputs(char *path) {
    FILE *fp = NULL;
    // "w+" 读写方式打开 如果文件不存在 则创建 如果文件存在 清空内容再写
    fp = fopen(path, "w+");
    if(fp == NULL) {
        ferror("my_fputs fopen");
        return;
    }

    // 写文件
    char *buf[] = {"123456\n", "bbbbbbbbbb\n", "cccccccccc\n"};
    int i = 0;
    int n = 3;
    for(i = 0; i < n ; i++) {
        // 返回值 成功是0 失败非0
        fputs(buf[i], fp);
    }

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}

void my_fgets(char *path) {
    FILE *fp = NULL;
    // 读写方式打开 如果文件不存在 则打开失败
    fp = fopen(path, "r+");
    if(fp == NULL) {
        ferror("my_fgets fopen");
        return;
    }

    char buf[100];
    // feof : file end 0f file
    while(!feof(fp)) {
        // sizeof(buf)最大值 只能放这么多 如果不超过 就实际大小存放
        // 返回值为成功读取的文件内容
        // 把"\n"作为换行的标识
        // fgets()读取完毕后 自动添加字符串结束符0
        char *p = fgets(buf, sizeof(buf), fp);
        if(p != NULL) {
            printf("p = %s", p);
            printf("buf = %s", buf);
        }
    }

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

}

void read_and_write_files_by_line() {
    my_fputs("../test.txt");
    my_fgets("../test.txt");
}

// 4、按照块读写文件
typedef struct {
    char name[50];
    int id;
} Stu;

void my_fwrite(char *path) {
    FILE *fp = NULL;
    // 读写方式打开 文件不存在就创建 文件存在就先清零 再写
    fp = fopen(path, "w+");
    if(fp == NULL) {
        ferror("my_fwrite fopen");
        return;
    }

    Stu s[3];
    char buf[50];
    int i = 0;
    for(i = 0 ; i < 3 ; i++) {
        sprintf(buf, "stu:%d%d%d", i, i, i);
        strcpy(s[i].name, buf);
        s[i].id = i + 1;
    }

    // 按块的方式写文件
    // s : 写入文件内容的内存首地址
    // sizeof(Stu) : 一块数据有多大
    // 3 : 写入了几块数据
    // ret : 成功写入文件的块数目
    int ret = fwrite(s, sizeof(Stu), 3, fp);
    printf("ret = %d\r\n", ret);

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

}

void my_fread(char *path) {
    FILE *fp = NULL;
    // 读写的方式打开 如果文件不存在 则打开失败
    fp = fopen(path, "r+");
    if(fp == NULL) {
        ferror("my_fread fopen");
        return;
    }

    Stu s[3];

    // 读文件 模块的方式读
    // s : 放文件内容的首地址
    // sizeof(Stu) : 块数据的大小
    // 3 : 块数 读文件数据的大小 sizeof(Stu) * 3
    // fp : 文件指针
    // 返回值 : 成功读取文件内容的块数目

    int ret = fread(s, sizeof(Stu), 3, fp);
    printf("ret = %d\r\n", ret);

    int i = 0;
    for(i = 0; i < 3; i++) {
        printf("%s, %d\r\n", s[i].name, s[i].id);
    }

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}

void read_and_write_files_in_blocks() {
    my_fwrite("../test.txt");
    my_fread("../test.txt");
}

// 5、按照格式化进行读写文件

void my_fprintf(char *path) {
    FILE *fp = NULL;
    // 读写方式打开 没有这个文件就创建 有这个文件就清零重新写
    fp = fopen(path, "w+");
    if(fp == NULL) {
        ferror("my_fprintf fopen");
        return;
    }

    printf("Hello World%d\r\n", 2);
    fprintf(stdout, "Hello World%d\r\n", 2);
    fprintf(fp, "Hello World%d\r\n", 2);


    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}

void my_fscanf(char *path) {
    FILE *fp = NULL;
    // 读写方式打开
    fp = fopen(path, "r+");
    if(fp == NULL) {
        ferror("my_fscanf fopen");
        return;
    }

    int a = 0;
    fscanf(fp, "Hello World%d\r\n", &a);
    printf("a = %d\r\n", a);

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}

void read_and_write_files_as_formatted() {
    my_fprintf("../test.txt");
    my_fscanf("../test.txt");
}

// 6、随机位置读文件
void read_files_at_random_locations() {
    FILE *fp = NULL;
    fp = fopen("../test.txt", "w+");
    if(fp == NULL) {
        ferror("read_files_at_random_locations fopen");
        return;
    }

    Stu s[3];
    Stu tmp;  // 读第三个结构体

    my_fwrite("../test.txt");

    fseek(fp, 2 * sizeof(Stu), SEEK_SET);
    // fseek(fp, -1 * sizeof(Stu), SEEK_END);
    int ret = 0;
    ret = fread(&tmp, sizeof(Stu), 1, fp);
    if(ret == 1) {
        printf("%s %d\r\n", tmp.name, tmp.id);
    }

    // 把文件光标移动到最开始的地方

    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}

/**
 *  work1
 *  1、将一个未知大小的文件（如song.txt）全部读入（不是一行一行的读取）内存 并显示在桌面上
 *  参考：fessk() ftell() rewind() fread() malloc()
 */

void work01() {
    char *buf = NULL;
    int maxsize = 1024;
    buf = (char *)malloc(maxsize * sizeof(char));
    FILE *fp = fopen("../work01.txt", "r+");
    if(fp == NULL) {
        printf("work01 fopen failed\r\n");
        return;
    }
    fread(buf, maxsize, 1, fp);
    printf("%s\r\n", buf);
    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    if(buf != NULL) {
        free(buf);
        buf = NULL;
    }
}

/**
 *  work02
 *  2、实现配置文件读写的功能 key = value格式
 *  a) 循环读每一行 如果此行包含key 则把key的value修改
 *  b) 如果所有行都不包含key 则在文件结尾追加 key = value
 *  c) 文件大小不能超过8K
 *  d) 参考 fgets() strstr() sprintf() strcat() fprintf()
 *          fputs() fseek() ftell() rewind()
 */

void work02() {
    int cmd = 0;
    char key[10] = {0};
    char value[50] = {0};
    char gets_buf[256] = {0};
    int i = 0;
    char *tmp = NULL;
    int begin = 0;
    int end = 0;
    int gets_len_last = 0, gets_len_all = 0, gets_len_now = 0;
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    while(1) {
        printf("===========================\r\n");
        printf("1 write\r\n");
        printf("2 read\r\n");
        printf("3 cls\r\n");
        printf("4 exit\r\n");
        printf("===========================\r\n");
        scanf("%d", &cmd);
        switch(cmd) {
            case 1: {
                printf("please enter the key:");
                scanf("%s", key);
                printf("\r\n");
                printf("please enter the value:");
                scanf("%s", value);
                printf("\r\n");
                break;
            }
            case 2: {
                printf("please enter the key:");
                scanf("%s", key);
                printf("\r\n");
                fp2 = fopen("../work02.txt", "r+");
                if(fp2 == NULL) {
                    printf("read failed\r\n");
                    break;
                }

                while(!feof(fp2)) {
                    fgets(gets_buf, sizeof(gets_buf), fp2);
                    tmp = strstr(gets_buf, key);
                    if (tmp != NULL) {
                        tmp += strlen(key) + 2;
                        end = strlen(tmp) - 1;
                        while (tmp[begin] == ' ') {
                            begin++;
                        }
                        while (tmp[end] == ' ' || tmp[end] == '\n') {
                            end--;
                        }
                        tmp += begin;
                        char out_buf[50] = {0};
                        strncpy(out_buf, tmp, end - begin + 1);
                        printf("%s : %s len = %d\r\n", key, out_buf, end - begin + 1);
                        begin = 0;
                        end = 0;
                        break;
                    }
                }

                if(tmp == NULL) {
                    printf("don't find the key\r\n");
                }

                if(fp2 != NULL) {
                    fclose(fp2);
                    fp2 = NULL;
                }

                break;
            }
            case 3: {
                system("cls");
                break;
            }
            default: {
                exit(0);
                break;
            }
        }
    }
}

int main() {
    setbuf(stdout,NULL);
    work02();
    // printf("Hello, World!\n");
    system("pause");
    return 0;
}
