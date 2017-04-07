#include "stdio.h"

void main() {
    int n;
    while (scanf("%d", &n) && n != 0) {
        while(n) {
            printf("%d", n % 10);
            n = n / 10;
        }
        printf("\n");
    }
}