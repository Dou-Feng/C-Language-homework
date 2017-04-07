#include "stdio.h"

void main() {
    double x0 = 0;
    double x = 9.0;
    while (x - x0 > 1e-6 || x0 - x > 1e-6) {
        x0 = x;
        x = x0 - (((3 * x0 - 4) * x0 - 5) * x0 + 13) / ((9 * x0 - 8) * x0 - 5);
    }
    printf("%lf\n", x);
}