//字符串复制
#include <stdio.h>

void mycpy(char s[], char t[], int n);

int main() {
    int N;
    scanf("%d", &N);
    getchar();
    for (int j = 0; j < N; ++j) {
        char c = '1';
        char t[1000], s[1000];
        int n = 0, i = 0;
        while ((c = getchar()) != '\n') {
            t[i] = c;
            i++;
        }
        t[i] = '\0';
        scanf("%d", &n);
        getchar();
        mycpy(s, t, n);
        printf("%s\n", s);
    }
}

void mycpy(char s[], char t[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        s[i] = t[i];
    }
    s[i] = '\0';
}