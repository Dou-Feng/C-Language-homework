#include <stdio.h>
#define BEGIN 4
#define END 200

void main() {
    int i,line;
    int number;
    int  j,k;
    int primeN[] = {2,3,5,7,11,13, 17,
                    19, 23, 29, 31, 37, 41,
                    43, 47, 53, 59, 61, 67,
                    71, 73, 79, 83, 89, 97,
                    101, 103, 107, 109, 113,
                    121, 127, 131, 137, 139,
                    149, 151, 157, 163, 167,
                    169, 173, 179, 181, 191,
                    193, 197, 199};
    scanf("%d", &line);
    for (i = 0;i < line; i++) {
        printf("请输入一个在4到200之间的偶数：\n");
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