#include "stdio.h"

int judge(int number);
void main() {
    int n;
    int line[40];
    for (int i = 0; i < 40; ++i) {
        line[i] = 0;
    }
    while (scanf("%d", &n) && n != 0) {
        int i;
        for (i = 0; i < n; ++i) {    /*遍历每一行，总共n行*/
            int j = 0;
            line[j] = 1;
            for (j = 1; j < i + 1; ++j) {   /*给每一行赋值*/
                    line[j] = line[j - 1] * (i - j + 1) / j;
                }
            for (int k = 0; k < 2 * (n - i - 1); ++k) {    /*输出前导空格*/
                printf(" ");
            }
            j = 0;
            while (j < i + 1) {                /*遍历每个元素*/
                if (j == i)                        /*当为最后一个赋值元素时*/
                    printf("%d\n", line[j]);
                else if (judge(line[j]) == 0 && judge(line[j + 1]) == 0) {
                    printf("%d   ", line[j]);
                } else if (judge(line[j]) == 0 && judge(line[j + 1]) == 1) {
                    printf("%d   ", line[j]);
                } else if (judge(line[j]) == 1 && judge(line[j + 1]) == 0){
                    printf("%d   ", line[j]);
                } else if (judge(line[j]) == 1 && judge(line[j + 1]) == 1) {
                    printf("%d  ", line[j]);
                } else if (judge(line[j]) == 1 && judge(line[j + 1]) == 2) {
                    printf("%d  ", line[j]);
                } else if (judge(line[j]) == 2 && judge(line[j + 1]) == 1) {
                    printf("%d  ", line[j]);
                } else if (judge(line[j]) == 2 && judge(line[j + 1]) == 2) {
                    printf("%d ", line[j]);
                }
                j++;
            }
        }
        printf("\n");
    }
}

int judge(int number) {
    int i;
    for (i = 0; (number /= 10) != 0; ++i);
    return i;
}