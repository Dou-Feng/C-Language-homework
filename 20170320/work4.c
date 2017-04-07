#include <stdio.h>

void main() {
    unsigned short x,m,n;
    unsigned short temp = 0;
    printf("x=");
    scanf("%hu",&x);
    printf("m=");
    scanf("%hu",&m);
    printf("n=");
    scanf("%hu",&n);
    x = x & (~temp >> (16 - n)) << m;
    x <<= 16-m-n;
    printf("%hu", x);
}
