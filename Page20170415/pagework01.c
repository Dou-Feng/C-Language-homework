//求三角形面积
#include <stdio.h>
#include <math.h>
#define s(a, b, c) ((a) + (b) + (c)) / 2
#define area(s, a, b, c) ((s) * ((s) - (a)) * ((s) - (b)) * ((s) - (c)))
int main() {
    int a, b, c;
    int ts;
    double result;
    while(scanf("%d%d%d",&a, &b, &c) != EOF) {
        ts = s(a, b ,c);
        result = sqrt(area(ts, a, b, c));
        printf("%d %lf\n", ts, result);
    }
}