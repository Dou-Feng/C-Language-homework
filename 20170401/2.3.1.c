#include "stdio.h"

//use for loop
int main() {
    int i, n, s = 1;
    printf("Please enter n:");
//    scanf("%d", n);       /*缺少&   ->   scanf("%d", &n)*/
    scanf("%d", &n);
//    for (int i = 0; i <= n; ++i) {         前面已经定义了 int i 所以不用再定义int i了  算法错误 i 应该从 1 开始
    while(i <= n) {
        s = s * i;
//        printf("%d!=%d", n, s);         printf 应该在for循环外面
        i++;
    }
    printf("%d!=%d", n, s);
    return 0;
}


//use while loop
#include "stdio.h"
int main() {
    int i, n, s = 1;
    printf("Please enter n:");
//    scanf("%d", n);       /*缺少&   ->   scanf("%d", &n)*/
    scanf("%d", &n);
//    for (int i = 0; i <= n; ++i) {         前面已经定义了 int i 所以不用再定义int i了  算法错误 i 应该从 1 开始
    for (i = 1; i <= n; ++i) {
        s = s * i;
//        printf("%d!=%d", n, s);         printf 应该在for循环外面
    }
    printf("%d!=%d", n, s);
    return 0;
}

//use do-while loop
#include "stdio.h"
int main() {
    int i, n, s = 1;
    printf("Please enter n:");
//    scanf("%d", n);       /*缺少&   ->   scanf("%d", &n)*/
    scanf("%d", &n);
    i = 1;
//    for (int i = 0; i <= n; ++i) {         前面已经定义了 int i 所以不用再定义int i了  算法错误 i 应该从 1 开始
    do {
        s = s * i;
        i++;
//        printf("%d!=%d", n, s);         printf 应该在for循环外面
    } while (i <= n);
    printf("%d!=%d", n, s);
    return 0;
}

//2.3.1(2)
#include "stdio.h"
int main() {
    int i, n = 0, S, s = 1;
    printf("Please enter S:");
    scanf("%d", &S);
    i = 1;
    do {
        s = s * i;
        i++;
        n++;
    } while (s < S);
    printf("%d\n", n);
    return 0;
}