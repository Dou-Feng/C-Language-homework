#include "stdio.h"

int main() {
    int t = 0;
    double n1 = 0, n2 = 0;
    char c = '1';
    while (scanf("%d  %lf  %lf %c", &t, &n1, &n2, &c) == 4) {
        if(t == 1) {
            switch (c) {
                case '+' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 + n2);
                    break;
                case '-' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 - n2);
                    break;
                case '*' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 * n2);
                    break;
                case '/' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 / n2);
                    break;
                default : 
                    break;
            }
        } else if (t == 0) {
            if (c == '+') {
                printf("After if-else processing,the result is : %.2lf\n", n1 + n2);
            } else if (c == '-') {
                printf("After if-else processing,the result is : %.2lf\n", n1 - n2);
            } else if (c == '*') {
                printf("After if-else processing,the result is : %.2lf\n", n1 * n2);
            } else if (c == '/') {
                printf("After if-else processing,the result is : %.2lf\n", n1 / n2);
            }
        } else if (t == 2) {
            if (c == '+') {
                printf("After if-else processing,the result is : %.2lf\n", n1 + n2);
            } else if (c == '-') {
                printf("After if-else processing,the result is : %.2lf\n", n1 - n2);
            } else if (c == '*') {
                printf("After if-else processing,the result is : %.2lf\n", n1 * n2);
            } else if (c == '/') {
                printf("After if-else processing,the result is : %.2lf\n", n1 / n2);
            }
            switch (c) {
                case '+' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 + n2);
                    break;
                case '-' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 - n2);
                    break;
                case '*' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 * n2);
                    break;
                case '/' : 
                    printf("After switch processing,the result is : %.2lf\n", n1 / n2);
                    break;
                default : 
                    break;
            }
        }
        printf("\n");
    }
    return 0;
}