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
	char *name = (char*)malloc(sizeof(char) * 1000);
	char *mac1 = (char*)malloc(sizeof(char) * 20);
	char *mac2 = (char*)malloc(sizeof(char) * 20);
	if(requestType && !strcmp(requestType, "GET")){
		readGetData(&data);
		//printf("The GET data is:\n\n");
	}if(data != (char *) 0){ 
		//printf("%s\n",data);
        char* temp;
		int i = 0;
       	temp = strtok(data, "=&");
		while(temp != NULL){
			switch(i++){
				case 1:
					memcpy(name, temp, sizeof(char) * 100);
					break;
				case 3:{
					memcpy(mac1, temp, sizeof(char) * 20);
					break;
				}case 5:{
					memcpy(mac2, temp, sizeof(char) * 20);
					break;
				}
				default: break;
			}
			//printf("%s\n", temp);
			temp = strtok(NULL, "=&");
		}
		
		FILE* fp = fopen("/www/DeviceList", "a");
		fprintf(fp, "%s %s %s\n", name, mac1, mac2);
		fclose(fp);
		free(name);
		free(mac1);
		free(mac2);
	}
	printf("OK!\n");
	exit(0);
}
