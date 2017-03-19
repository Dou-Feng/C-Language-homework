#include "stdio.h"

enum month { Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec};

int main() {
	enum month month;
	int list[] =  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char *list2[] = { "January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December"};
	int x;
	scanf("%d", &x);
	if ( x % 4 && !(x % 100) || x % 400) {
		list[1] = 29;
	}
	for(month = Jan; month <= Dec; month++) {
		printf("%s,%d\n", list2[month], list[month]);
	}
	return 0;
}