//游戏：掷骰子
#include "stdio.h"

int getSum(int n) {
    int i= 0;
    int sum = 0;
    while(n != 0) {
        sum += n % 10;
        n /= 10;
        i++;
    }
    return sum;
}

int playResult(int a, int b, int n) {
    int sumA = getSum(a + n - 1), sumB = getSum(b + n - 1);
    //printf("%d   %d\n", sumA, sumB);
    int finalResult = 0, result1 = 0, result2 = 0;
    result1 = sumA % 6 + 1;
    result2 = sumB % 6 + 1;
    finalResult = result1 + result2;
    return finalResult;
}

void judgement() {
    int a, b;
    int time = 1;
    int Sum = 0, other = 0;
    scanf("%d%d", &a, &b);
    Sum = playResult(a, b, time);
        if (Sum == 11 || Sum == 7) {
            printf("success!\n");
        } else if (Sum == 2 || Sum == 3 || Sum == 12) {
            printf("fail!\n");
        } else {
            other = Sum;
            int bool = 1;
            do {
                Sum = playResult(a, b, ++time);
                if (Sum == 7) {
                    bool = 0;
                    printf("fail!\n");
                    break;
                }
            } while (Sum != other);
            if (bool != 0)
                printf("success!\n");
        }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        judgement();
    }
    return 0;
}