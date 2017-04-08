#include "stdio.h"

int getNumber(unsigned long n, int k);
int getLength(unsigned long n);

int main()
{
    unsigned long n = 0;
    int k = 0;
    while (scanf("%lu%d", &n, &k) != EOF) {
        printf("%d\n", getNumber(n, k));
    }
    return 0;
}

int getNumber(unsigned long n, int k)
{
    if (k > getLength(n)) {
        return -1;
    }
    else {
        for (int i = 0; i < k - 1; ++i) {
            n /= 10;
        }
    }
    return n % 10;
}

int getLength(unsigned long n) {
    int i= 0;
    while(n != 0) {
        n /= 10;
        i++;
    }
    return i;
}