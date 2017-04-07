#include "stdio.h"

void main() {
    double n;
    while (scanf("%lf", &n) && n - 0 > 0.0000001) {
        if (n <= 1000) {
            printf("%lf\n", 0.0 * n);
        } else if (n > 1000 && n <= 2000) {
            printf("%lf\n", 0.05 * (n - 1000));
        } else if (n > 2000 && n <= 3000) {
            printf("%lf\n", 0.10 * (n - 2000) + 50);
        } else if (n > 3000 && n <= 4000) {
            printf("%lf\n", 0.15 * (n - 3000) + 150);
        } else if (n > 4000 && n <= 5000) {
            printf("%lf\n", 0.20 * (n - 4000) + 300);
        } else {
            printf("%lf\n", 0.25 * (n - 5000) + 500);
        }
    }
}