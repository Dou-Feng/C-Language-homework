//十六进制字符转整数
#include <stdio.h>

int chg(char *s) {
    int sum = 0;
    s++,s++;
    while (*s != '\0') {
        if (*s >= 'A' && *s <= 'F')
            sum = sum * 16 + *s - 'A' + 10;
        else if (*s >= 'a' && *s <= 'f')
            sum = sum * 16 + *s - 'a' + 10;
        else
            sum = sum * 16 + *s -'0';
        s++;
    }
    return sum;
}

int main() {
    int N;
    char a[100];
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%s", a);
        printf("%d\n", chg(a));
    }
}