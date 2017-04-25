//选择排序
#include <stdio.h>

void selectRank(int array[], int n);

int main() {
    int n;
    int s[21];
    while (scanf("%d", &n) && n != 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &s[i]);
        }
        selectRank(s, n);
        for (int j = n - 1; j >= 0; --j) {
            if (j != 0)
                printf("%d ", s[j]);
            else
                printf("%d\n", s[j]);
        }
    }
    return 0;
}

void selectRank(int array[], int n) {
    int position;
    int max;
    for (int i = 0; i < n; ++i) {
        position = i;
        max = array[i];
        for (int j = i; j < n; ++j) {
            if (max < array[j]) {
                max = array[j];
                position = j;
            }
        }
        if (position != i) {
            array[position] =array[i];
            array[i] = max;
        }
    }
}