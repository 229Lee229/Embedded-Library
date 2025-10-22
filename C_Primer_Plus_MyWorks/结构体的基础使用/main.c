#include <stdio.h>


int main()
{
	struct Student{
		char name[50];
		int age;
		float score;
	}stu;
	scanf("%s %d %f",stu.name,&stu.age,&stu.score);
	printf("name:%s\r\nage:%d\r\n,score:%.4f\n",stu.name,stu.age,stu.score);
	// printf("name:%s\r\n",stu.name);
	// printf("age:%d\r\n",stu.age);
	// printf("score:%f\r\n",stu.score);
	printf("Done.\n");
}