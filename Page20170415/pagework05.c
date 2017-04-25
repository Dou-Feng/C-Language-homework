//统计数字和字符个数
#include <stdio.h>

int main() {
    int total[12];
    for (int i = 0; i < 12; ++i) {
        total[i] = 0;
    }
    char c;
    while ((c = getchar()) != '#') {
        if (c >= '0' && c <= '9') {
            total[c - '0']++;
        } else if (c >='A' && c <= 'Z' || c >= 'a' && c <= 'z') {
            total[10]++;
        } else {
            total[11]++;
        }
    }
    for (int j = 0; j < 10; ++j) {
        printf("Number %d: %d\n", j, total[j]);
    }
    printf("characters: %d\nother: %d\n", total[10], total[11]);
}