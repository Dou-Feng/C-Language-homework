#include "stdio.h"

void main() {
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i) {
        char c;
        int state = 0;
        while ((c = getchar()) != '\n') {
            if (c == ' ' && state == 1) {
                continue;
            } else {
                state = 0;
            }
            if (c == ' ') {
                state = 1;
            }
            putchar(c);
        }
        printf("\n");
    }
}