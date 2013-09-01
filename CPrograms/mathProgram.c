#include "math.h"
#include<stdio.h>
#include<stdlib.h>

int main() {

int x, y;

printf("Enter number two numbers then enter:\n");
scanf("%d%d", &x, &y);
printf("The sum of %d and %d is : %d \n", x, y, sumInt(x, y));
printf("The factorial of %d is: %d \n",x, factorial(x));
printf("The square of %d is: %d \n",x, squareInt(x));

printf("The factorial of square(%d) is: %d \n",x, factorial(squareInt(x)));
exit(0);
}
