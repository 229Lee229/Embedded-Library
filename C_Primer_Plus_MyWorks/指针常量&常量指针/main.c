#include "stdio.h"


int main()
{
	// test HARM_MEAN
	int x = 10;
	int y = 20;
	int *const a = &x;
	printf("a = %d\r\n",*a);
	const int *b = &x;
	printf("b = %d\r\n",*b);
	// a = &y;				// 这行会报错   原因:指向不可变
	*a = y;
	b = &y;					// 指向可变
	// *b = y;					// 这行会报错	原因:值不可变

	printf("a1 = %d\r\n",*a);			// 值可变
	printf("b1 = %d\r\n",*b);
	printf("x = %d\r\n",x);				// 地址的x也跟着变
	printf("Done.\r\n");
}