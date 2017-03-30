#include <stdio.h>

void main() {
    int i,line;
    int number;
    int  j,k;
    int primeN[] = {2,3,5,7,11,13, 17, 19, 23, 29, 31, 37, 41,
                    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    scanf("%d", &line);
    for (i = 0;i < line; i++) {
        int temp = 0;
        scanf("%d", &number);
        for (j = 24; j > -1; j--) {
                for (k = 0; k < 25; ++k) {
                    if (number == primeN[j] + primeN[k]) {
                        temp = printf("%d=%d+%d\n", number, primeN[k], primeN[j]);
                        break;
                    }
                }
            if (temp) {
                break;
            }
        }
    }
}