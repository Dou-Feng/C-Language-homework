#include "stdio.h"

int main() {
    int list[32];
	int list2[32];
    unsigned int x;
	int n, p;
	int i;
    int length = sizeof (int) * 8;
    scanf("%d %d %d", &x, &p, &n);
	int x1 = x;
	if (x1 >= 0) {
        for (i = 31; i > -1; i--) {
            list2[i] = x1 % 2;
            x1 /= 2;
        }
    } else {
        x1 = -x1;
		list2[0] = 1;
        for (i = 31; i > 0; i--) {
            list2[i] = x1 % 2;
            x1 /= 2;    
        }
	}
	for (i = 0; i < 32; i++) {
        printf("%d", list2[i]);
        if (i == 31) {
        printf("\n");
            break;
		}
        if ((i + 1) % 8 == 0)
            printf(" ");
    } 
    x = x ^ ((~0U >> (length - n)) << p);
    if (x >= 0) {
        for (i = 31; i > -1; i--) {
            list[i] = x % 2;
            x /= 2;
        }
    } else {
        x = -x;
		list[0] = 1;
        for (i = 31; i > 0; i--) {
            list[i] = x % 2;
            x /= 2;    
        }
	}
    for (i = 0; i < 32; i++) {
        printf("%d", list[i]);
		if (i == 31) {
			printf("\n");
            break;
		}
        if ((i + 1) % 8 == 0)
            printf(" ");
    }
    return 0;
}