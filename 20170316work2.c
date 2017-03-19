#include "stdio.h" 

int main() {
	unsigned int x;
	int n,i;
	int length = sizeof (int) * 8;
	scanf("%d %d", &x, &n);
	for (i = 0; i < n; i++) {
		x = x >> 1 | x << (length -1);
	}
	printf("%d", x);
	return 0;
}