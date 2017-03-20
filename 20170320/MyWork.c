#include <stdio.h>
//#define PI 3.14159;
#define PI 3.14159

int main(void) {
    int f;
    short p,k;
    double c,r,s;
    /*for task 1*/
    printf("Input Fahrenheit:");
    //scanf("%d", f);    /*the scanf need '&' in front of 'f'*/
    scanf("%d", &f);
    //c = 5/9 * (f-32);   /*the double need the (double) to get right data*/
    c = (double) 5/9 * (f-32);
    printf("\n%d(F)=%.2lf(C)\n\n",f,c);
    /*for task 2*/
    printf("input the radius r:");
    scanf("%lf", &r);   //need %lf
    s = PI * r * r;
    //printf("\nThe acreage is %.2f\n\n",&s);   /*the printf don't need '&' before 's'*/
                                                /*the double need %lf to output*/
    printf("\nThe acreage is %.2lf\n\n", s);
    /*for task 3*/
    printf("input hex int k,p:");
    scanf("%x %x", &k, &p);
    /*declare short int newint*/
    short newint;//newint undeclared
    //newint = (p&0xff00)|(k&0xff00)<<8;  /*the statement is wrong*/
      newint = (p&0xff00)|(k>>8)&0xff;
    printf("newint =%hx\n\n",newint);   //  应该使用hx
}
