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
	// a = &y;				// ���лᱨ��   ԭ��:ָ�򲻿ɱ�
	*a = y;
	b = &y;					// ָ��ɱ�
	// *b = y;					// ���лᱨ��	ԭ��:ֵ���ɱ�

	printf("a1 = %d\r\n",*a);			// ֵ�ɱ�
	printf("b1 = %d\r\n",*b);
	printf("x = %d\r\n",x);				// ��ַ��xҲ���ű�
	printf("Done.\r\n");
}