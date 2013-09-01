#include<stdio.h>
#include<stdlib.h>
#include "math.h"

int factorial(int x) {
int fac = 1;

while(x > 0){
fac*=x;
x--;
}
return fac;
}
