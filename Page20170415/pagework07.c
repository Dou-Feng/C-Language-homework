//电文大小写转化
#include <stdio.h>
#define CHANGE ((s) % 2)

int main() {
    int N;
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; ++i) {
        char c[1000];
        fgets(c, 1000, stdin);
        char s = c[0];
        if (CHANGE == 1) {
            for (int j = 0; c[j] != '\0'; ++j) {
                if (c[j] >= 'a' && c[j] <= 'z')
                    c[j] = c[j] - 'a' + 'A';
                else if (c[j] >= 'A' && c[j] <= 'Z')
                    c[j] = c[j] + 'a' - 'A';
            }
            printf("%s", c);
        } else if (CHANGE == 0) {
            printf("%s", c);
        }
    }
}