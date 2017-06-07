#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void main(int argc, char *argv[]){
	printf("Content-type : text/html\n\n");
	FILE* fp = fopen("/www/forwarding.sh", "r");
	char* str = (char*)calloc(sizeof(char), 1024);
	printf("<HTML><body><table><tr><td>IN PORT</td><td>OUT PORT<td>DEL</td></tr>");
	int i = 0;
	while(fgets(str, 1024, fp)){
		int in;
		char* ip = (char*)calloc(sizeof(char), 20);
		memset(ip, 0x00, sizeof(char) * 20);
		sscanf(str, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d %*s %*s %*s %s", &in, ip);
		printf("<tr><td>%d</td><td>%s</td><td><button onclick=\"window.location.href=\'https://192.168.1.1/cgi-bin/del?in=%d\'\">del</button></td></tr>", in, ip, i++);
		fgets(str, 1024, fp);
		free(ip);
	}
	printf("</table></body></HTML>");
	fclose(fp);
	free(str);
	exit(0);
}
