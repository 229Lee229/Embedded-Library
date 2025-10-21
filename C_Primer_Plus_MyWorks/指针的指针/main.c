#include <stdio.h>


int main()
{
	int val = 5;
	int *p = &val;
	printf("val = %d\r\n",val);
	printf("*p = %d\r\n",*p);
	int **pp = &p;
	printf("**pp = %d\r\n",**pp);

	**pp = 10;
	printf("modify after:\r\n");
	printf("*p = %d\r\n",*p);
	printf("val = %d\r\n",val);
	printf("Done.\n");
}