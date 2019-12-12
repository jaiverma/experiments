#include <stdio.h>
#include <string.h>

char *lstrip(char *s, char *t) {
    while (*s != '\0' && *t != 0 && *s == *t) {
        s++;
        t++;
    } 
    return s;
}

int main() {
    char in[] = "/mnt/ccc/xenial/aflout/queue/id:000001,time:0,orig:8_Channel_ID.m4a";
    char out[] = "/mnt/ccc/xenial/aflout/chunks/id:000001,time:0,orig:8_Channel_ID.m4a.repaired";
    char s[] = "/mnt/ccc/xenial";
    printf("in: %s\n", lstrip(in, s));
    printf("out: %s\n", lstrip(out, s));
}
