#include "stdio.h"

void hailstone(int n);

int main() {
    int n;
    while (scanf("%d", &n) && n != 0) {
        hailstone(n);
        printf("\n");
    }

    return 0;
}

void hailstone(int n) {
    int i = 0;
    while (n != 1) {
        printf("%5d", n);
        i++;
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        if (i % 6 == 0)
            printf("\n");
    }
    printf("%5d\n", n);
}