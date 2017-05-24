#include <stdio.h>
#include <string.h>
#include <inttypes.h>

void main(){
	uint64_t* test = (uint64_t*)malloc(sizeof(uint64_t*));
	printf("%d", sizeof(test));
}
