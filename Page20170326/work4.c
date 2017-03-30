#include "stdio.h"

void main() {
    int N;
    int i;
    char x;
    scanf("%d", &N);
    getchar();    //神奇的getchar（）
    for (i = 0; i < N; ++i) {
        scanf("%c", &x);
        getchar();   //神奇的getchar（）
        if (x >= 'a' && x <= 'f') {
            printf("%d\n", 10 + x - 'a');
        } else if (x >= '0' && x <= '9') {
            printf("%d\n", x - '0');
        } else if (x >= 'A' && x <= 'F') {
            printf("%d\n", x - 'A' + 10);
        } else {
            printf("%d\n", x);
        }
    }
}
