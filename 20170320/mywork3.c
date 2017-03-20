#include <stdio.h>

void main() {
    char c;
    scanf("%c", &c);
    printf("%c\n",(c>='A'&&c<='Z')?c-'A'+'a':c);
}
