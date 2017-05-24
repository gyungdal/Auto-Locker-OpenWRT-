#include <stdio.h>
#include <stdlib.h>

void main(){
int *a={1,2,3};
int b[3] = {4,5,5};
a=&b;
printf("%d",*(a));
}
