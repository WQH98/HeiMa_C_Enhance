#include "stdio.h"

int getStr1Str2(char *source, char *buf1, char *buf2) {
    if(source == NULL || buf1 == NULL || buf2 == NULL) {
        return -1;
    }
    int i = 0;
    int j = 0;
    int k = 0;

    while(source[i] != 0) {
        if(i % 2 == 0) {
            *buf1 = source[i++];
            buf1++;
            // buf1[j++] = source[i++];
        }
        else {
            *buf2 = source[i++];
            buf2++;
            // buf2[k++] = source[i++];
        }
    }

    *buf1 = 0;
    *buf2 = 0;

    return 0;
}

int main() {
    char *p = "1a2b3c4d";
    char buf1[100] = {0};
    char buf2[100] = {0};
    getStr1Str2(p, buf1, buf2);
    printf("buf1 = %s\r\nbuf2 = %s\r\n", buf1, buf2);

    return 0;
}
