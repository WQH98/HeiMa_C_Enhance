#include "stdio.h"
#include "string.h"

int getKeyByValue(char *keyvaluebuf, char *keybuf, char *valuebuf, int *valuebuflen) {
    if(keyvaluebuf == NULL || keybuf == NULL || valuebuf == NULL || valuebuflen == NULL) {
        return -1; // 传入的有空指针
    }

    if(strstr(keyvaluebuf, keybuf) == NULL) {
        return -2; // 未找到子串
    }

    char *str = strstr(keyvaluebuf, "=");

    str += 1;

    int begin = 0;
    int end = 0;
    int i = 0;
    while(str[i++] == ' ');
    begin = i - 1;
    while(str[i] != ' ') {
        i++;
        if(str[i] == 0)
        break;
    }
    end = i - 1;

    *valuebuflen = end-begin+1;
    strncpy(valuebuf, str+begin, *valuebuflen);
    valuebuf[*valuebuflen] = 0;

    return 0;

}

int main() {
    char *key1 = "key1 = value1";
    char *key2 = "key2 =         value2";
    char *key3 = "key3   = value3";
    char *key4 = "key4            = value4";
    char *key5 = "key5 =";

    char buf[100] = {0};
    int len = 0;

    getKeyByValue(key5, "key5", buf, &len);

    printf("buf = %s\r\n", buf);

    return 0;
}
