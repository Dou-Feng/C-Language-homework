//判断回文数
#include <stdio.h>
#include <string.h>

int isReg(char *s) {
    int length = strlen(s);
    if (length == 1 || length == 0) {
        return 1;
    }
    if (*s == *(s + length - 1)) {
        *(s + length - 1) = '\0';
        return isReg(s + 1);
    }
    else
        return 0;
}

int main() {
    int N;
    scanf("%d",&N);
    getchar();
    char s[200];
    for (int i = 0; i < N; ++i) {
        char c = '0';
        int j = 0;
        while ((c = getchar()) != '\n') {
            s[j] = c;
            j++;
        }
        s[j] ='\0';
        if (isReg(s))
            printf("Yes!\n");
        else
            printf("No!\n");
    }
}