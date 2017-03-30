#include "stdio.h"

void main() {
    int s1, s2, s3;
    while (scanf("%d %d %d", &s1, &s2, &s3) != EOF) {
       if (s1 == s2 && s1 == s3) {
           printf("A:%d\n", s1);
       } else if (s1 == s2) {
           printf("A:%d\n", s1);
       } else if (s2 == s3) {
           printf("B:%d\n", s2);
       } else if (s1 == s3) {
           printf("A:%d\n", s1);
       } else if (s1 > s2 && s1 < s3) {
           printf("A:%d\n", s1);
       } else if (s1 > s2 && s1 > s3) {
           if (s2 > s3) {
               printf("B:%d\n", s2);
           } else {
               printf("C:%d\n", s3);
           }
       } else if (s1 < s2 && s1 > s3) {
           printf("A:%d\n", s1);
       } else if (s1 < s2 && s1 < s3) {
           if (s2 > s3) {
               printf("C:%d\n", s3);
           } else {
               printf("B:%d\n", s2);
           }
       }
    }
}