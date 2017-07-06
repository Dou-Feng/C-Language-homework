//字符串长度
#include <malloc.h>
#include "stdio.h"

int strLen(char *s) {
    if (*s == '\0')
        return 0;
    else
        return strLen(s + 1) + 1;
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i) {
        char *s;
        s = malloc(100);
        int j = 0;
        char c;
        while((c = getchar()) != '\n') {
            *(s++) = c;
            j++;
        }
        *s = '\0';
        printf("%d\n", strLen(s - j));
    }
}