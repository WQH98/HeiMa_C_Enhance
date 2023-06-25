#include <stdio.h>
#include <string.h>

// 2
int trimSpace(char *inbuf, char *outbuf) {
    int i = 0;
    int bigen = 0;
    int end = 0;
    if(inbuf == NULL || outbuf == NULL) {
        return -1;
    }
    while(inbuf[i++] == ' ');
    bigen = i - 1;
    while(inbuf[i++] != ' ');
    end = i - 1;

    strncpy(outbuf, inbuf + bigen, end - bigen + 1);

    return 0;
}

int main() {
    char *p = "      abcdef        ";
    char buf[100] = {0};
    trimSpace(p, buf);
    printf("buf : %s\r\n", buf);
    return 0;
}


