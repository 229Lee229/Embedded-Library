/*  两数的调和平均数这样计算：先得到两数的倒数，然后计算两个倒数的平均值，最后取计算结果的倒数。
    使用#define指令定义一个宏“函数”，执行该运算。编写一个简单的程序测试该宏。*/


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