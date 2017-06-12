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


char *replaceAll(char *s, const char *olds, const char *news) {
  char *result, *sr;
  size_t i, count = 0;
  size_t oldlen = strlen(olds); if (oldlen < 1) return s;
  size_t newlen = strlen(news);


  if (newlen != oldlen) {
    for (i = 0; s[i] != '\0';) {
      if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
      else i++;
    }
  } else i = strlen(s);


  result = (char *) malloc(i + 1 + count * (newlen - oldlen));
  if (result == NULL) return NULL;


  sr = result;
  while (*s) {
    if (memcmp(s, olds, oldlen) == 0) {
      memcpy(sr, news, newlen);
      sr += newlen;
      s  += oldlen;
    } else *sr++ = *s++;
  }
  *sr = '\0';

  return result;
}

void main(int argc, char *argv[]){
	char *requestType;
	char *data = (char *) 0;
	printf("Content-type : text/plain\n\n");
	//printf("The GET data is :\n\n");
	requestType = getenv("REQUEST_METHOD");
	char *name = (char*)malloc(sizeof(char) * 1000);
	char *mac1 = (char*)malloc(sizeof(char) * 40);
	char *mac2 = (char*)malloc(sizeof(char) * 40);
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
					memcpy(mac1, temp, sizeof(char) * 40);
					mac1 = replaceAll(mac1, "%3A", ":");
					break;
				}case 5:{
					memcpy(mac2, temp, sizeof(char) * 40);
					mac2 = replaceAll(mac2, "%3A", ":");
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
