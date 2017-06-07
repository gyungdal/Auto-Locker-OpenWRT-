#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void readGetData(char **aString){
	char *queryString;
	int len=0;
	queryString=getenv("QUERY_STRING");
	if(queryString){
		len = strlen(queryString);
		*aString=malloc(sizeof(char) *len);
		strcpy(*aString, queryString);
	}else{
		len=1;
		*aString = malloc(sizeof(char) *len);
		**aString = '\0';
	}
}

void main(int argc, char *argv[]){
	char *requestType;
	char *data = (char *) 0;
	printf("Content-type : text/plain\n\n");
	//printf("The GET data is :\n\n");
	requestType = getenv("REQUEST_METHOD");
	char *in = (char*)malloc(sizeof(char) * 10);
	char *out = (char*)malloc(sizeof(char) * 10);
	char *port = (char*)malloc(sizeof(char) * 100);
	if(requestType && !strcmp(requestType, "GET")){
		readGetData(&data);
		//printf("The GET data is:\n\n");
	}if(data != (char *) 0){ 
		//printf("%s\n",data);
        	char* temp;
		int i = 0;
       		temp = strtok(data, "=&");
        	char* command = (char*)malloc(sizeof(char) * 1024);
		memset(command, ' ', sizeof(char) * 1024);
		while(temp != NULL){
			switch(i++){
				case 1:
					memcpy(in, temp, sizeof(char) * 1024);
					sprintf(command, "ifconfig eth0 %s netmask ", temp);
					//printf(command);
					break;
				case 3:{
					memcpy(ip, temp, sizeof(char) * 1024);
					FILE* fp = fopen("/www/ip.sh", "a");
					char* t = (char*)malloc(sizeof(char) * 1024);
					sprintf(t, "%s%s\n", command, temp);
					memmove(command, t, sizeof(char) * 1024);
					free(t);
					//strncat(command, temp, sizeof(temp) / sizeof(char));
					printf(command);
					system(command);
					fprintf(fp, command);
					fclose(fp);
					break;
				}case 5:{
					memcpy(port, temp, sizeof(char) * 1024);
					FILE* fp = fopen("/www/ip.sh", "a");
					memset(command, ' ', sizeof(char) * 1024);
					sprintf(command, "route add default gw %s eth0\n", temp);
					printf(command);
					fprintf(fp, command);
					fclose(fp);
					system(command);
					break;
				}
				default: break;
			}
                	//printf("%s\n", temp);
               		temp = strtok(NULL, "=&");
        	}
		FILE* fp = fopen("/www/forwarding.sh", "a");
		
		free(command);
	}
	exit(0);
}
