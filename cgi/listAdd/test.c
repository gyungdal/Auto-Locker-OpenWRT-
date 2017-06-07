#include <stdio.h>
#include <string.h>

void main(){
	char test[] = "ip=192.168.1.1&subnet=192.168.1.1&gateway=192.168.1.1&submit=%%EC%8B%%A4%%ED%96%89";
	char* temp;
	temp = strtok(test, "=&");
	while(temp != NULL){
		printf("%s\n", temp);
		temp = strtok(NULL, "=&");
	}	
}
