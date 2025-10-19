#include "stdio.h"


void swap(int *a,int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;


}

int main()
{
	// test HARM_MEAN

	int a,b;
	scanf("%d%d",&a,&b);
	swap(&a,&b);
	printf("a = %d\nb = %d\n",a,b);
	puts("Bye.");
}