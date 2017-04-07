#include "stdio.h"

void main() {
    int number;
    printf("Please input a integer:");
    scanf("%d",&number);
    int p1,p2,p3,p4;
    p1 = number >> 24 & 0xff;
    p2 = number >> 16 & 0xff;
    p3 = number >> 8 & 0xff;
    p4 = number & 0xff;
    printf("%d.%d.%d.%d", p4,p3,p2,p1);
}
