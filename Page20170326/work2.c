#include "stdio.h"

void main() {
    int t;
    float n1, n2;
    char c;
    while (scanf("%d %f %f %c", &t, &n1, &n2, &c) != EOF) {
        getchar();
        if(t == 1) {
            switch (c) {
                case '+':
                    printf("After switch processing,the result is : %.2f\n", n1 + n2);
                    break;
                case '-':
                    printf("After switch processing,the result is : %.2f\n", n1 - n2);
                    break;
                case '*':
                    printf("After switch processing,the result is : %.2f\n", n1 * n2);
                    break;
                case '/':
                    printf("After switch processing,the result is : %.2f\n", n1 / n2);
                    break;
                default:
                    break;
            }
        } else if (t == 0) {
            if (c == '+') {
                printf("After if-else processing,the result is : %.2f\n", n1 + n2);
            } else if (c == '-') {
                printf("After if-else processing,the result is : %.2f\n", n1 - n2);
            } else if (c == '*') {
                printf("After if-else processing,the result is : %.2f\n", n1 * n2);
            } else if (c == '/') {
                printf("After if-else processing,the result is : %.2f\n", n1 / n2);
            }
        } else if (t == 2) {
            if (c == '+') {
                printf("After if-else processing,the result is : %.2f\n", n1 + n2);
            } else if (c == '-') {
                printf("After if-else processing,the result is : %.2f\n", n1 - n2);
            } else if (c == '*') {
                printf("After if-else processing,the result is : %.2f\n", n1 * n2);
            } else if (c == '/') {
                printf("After if-else processing,the result is : %.2f\n", n1 / n2);
            }
            switch (c) {
                case '+':
                    printf("After switch processing,the result is : %.2f\n", n1 + n2);
                    break;
                case '-':
                    printf("After switch processing,the result is : %.2f\n", n1 - n2);
                    break;
                case '*':
                    printf("After switch processing,the result is : %.2f\n", n1 * n2);
                    break;
                case '/':
                    printf("After switch processing,the result is : %.2f\n", n1 / n2);
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}