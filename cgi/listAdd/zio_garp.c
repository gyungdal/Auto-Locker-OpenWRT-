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
	char *numText = (char*)malloc(sizeof(char) * 100);
	long num = -1;
	if(requestType && !strcmp(requestType, "GET")){
		readGetData(&data);			
		//printf("The GET data is:\n\n");
	}if(data != (char *) 0){ 
		//printf("%s\n",data);
        char* temp;
		char* oneIp = (char*)calloc(sizeof(char), 1024);
		char* twoIp = (char*)calloc(sizeof(char), 1024);
		char* name = (char*)calloc(sizeof(char), 1024);	
		int i = 0;
		temp = strtok(data, "=&");
		char* command = (char*)malloc(sizeof(char) * 1024);
		memset(command, ' ', sizeof(char) * 1024);
		while(temp != NULL){
			switch(i++){
				case 1:
					memcpy(name, temp, sizeof(char) * 1024);
					break;
				case 3:
					memcpy(oneIp, temp, sizeof(char) * 1024);
					break;
				case 5:
					memcpy(twoIp, temp, sizeof(char) * 1024);
					break;
				default: break;
			}
			//printf("%s\n", temp);
			temp = strtok(NULL, "=&");
		}
		FILE* fp = fopen("/www/DeviceList", "a");
		fprintf("%s %s %s\n", name, oneIp, twoIp);
		fclose(fp);
		free(oneIp);
		free(twoIp);
		free(name);
		free(command);
	}
	exit(0);
}
