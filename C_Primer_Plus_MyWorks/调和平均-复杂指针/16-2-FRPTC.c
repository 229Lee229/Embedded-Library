/*  �����ĵ���ƽ�����������㣺�ȵõ������ĵ�����Ȼ���������������ƽ��ֵ�����ȡ�������ĵ�����
    ʹ��#defineָ���һ���ꡰ��������ִ�и����㡣��дһ���򵥵ĳ�����Ըúꡣ*/


#include "stdio.h"
#include "math.h"
#include "assert.h"
#include <limits.h>


#define Reciprocal(x) 1./(x)
#define SumMean(x,y)    Reciprocal((Reciprocal(x)+Reciprocal(y))/2)
typedef char(*(* FRPTC)())[5];

char (*foo())[5]{
	static char arr[5] = {'a','b','c','d','\0'};
	return &arr;
}

void FRPTC_Func(){
    FRPTC F = foo;
    char (*result)[5] = F();

    printf("%d\r\n",sizeof(*result));
    for(int i = 0;i < sizeof(*result);i++){
        printf("%c\t",(*result)[i]);
    }


}

void SumMean_Func(){
    double x,y;
    while(scanf("%lf%lf",&x,&y) == 2){
        printf("The SumMean is %lf\r\n",SumMean(x,y));

        printf("Next one:\r\n");
    }
    
    printf("Done\r\n");


}
int main(){
    printf("test\r\n");

    // part 1
    FRPTC_Func();
    puts("\n");

    // part 2
    SumMean_Func();
    return 0;
}