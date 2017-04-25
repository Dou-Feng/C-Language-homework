//使用了其他数组存放，不是一个好方法
#include <stdio.h>

int *exchange(int array[],int n, int k);

int main()  {
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF) {
        int array[n + 1000];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &array[i]);
        }
        exchange(array, n, k);
        for (int j = 0; j < n; ++j) {
            printf("%d", array[j]);
            if (j != n - 1)
                printf(" ");
        }
        printf("\n");
    }
}

int *exchange(int array[],int n,int k) {
    int i;
    for (i = 0; i < k; ++i) {
        array[i+ 1000] = array[i];
    }
    for (int j = k; j < n; ++j) {
        array[j - k] = array[j];
    }
    for (int l = i - 1; l >= 0; --l) {
        array[n - 1 + l - i + 1] =  array[l + 1000];
    }
}