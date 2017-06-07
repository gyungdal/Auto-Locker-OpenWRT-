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
		int i = 0;
		temp = strtok(data, "=&");
		char* command = (char*)malloc(sizeof(char) * 1024);
		memset(command, ' ', sizeof(char) * 1024);
		while(temp != NULL){
			switch(i++){
				case 1:
					memcpy(numText, temp, sizeof(char) * 100);
					num = atol(numText);
					free(numText);
					break;
				default: break;
			}
			//printf("%s\n", temp);
			temp = strtok(NULL, "=&");
		}
		system("rm -rf /www/DeviceList.345678temp");
		FILE* fp = fopen("/www/DeviceList", "r");
		FILE* ftp = fopen("/www/DeviceList.345678temp", "w");
		int numTemp = 0;
		if(num != -1){
			char* temp = (char*)malloc(sizeof(char) * 1024);
			while(fgets(temp, 1024, fp)){
				if(numTemp != num){
						fputs(temp, ftp);
				}
				numTemp += 1;
			}
			free(temp);
			fclose(fp);
			fclose(ftp);
			system("rm -rf /www/DeviceList");
			system("mv /www/DeviceList.345678temp /www/DeviceList");
			system("rm -rf /www/DeviceList.345678temp");
		}
	}
	exit(0);
}
