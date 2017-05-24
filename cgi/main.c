#include "list.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* ip;
	char* mac;
} IPInfo;

typedef struct {
	char* mac;
	int strength;
	char* name;
} MacInfo;

typedef struct {
	IPInfo ipInfo;
	MacInfo rssiInfo;
} Info;

IPInfo readIPMac(char* str){
	char* ip = (char*)malloc(sizeof(char) * 20);
	char* mac = (char*)malloc(sizeof(char) * 20);
	sscanf(str, "%*s %s %s %*s %*s", mac, ip);
	IPInfo info;
	info.ip = ip;
	info.mac = mac;
	return info;
}

int getStrength(char* mac, char* str){
	if(strncasecmp(mac, str, strlen(mac) -1) == 0){
		int power;
		char* name = (char*)malloc(sizeof(char) * 1024);
		sscanf(str, "%*s %d %*s %*s %s %*s", &power, name);
		printf("NAME : %s\n", name);
		return power;
	}
	return 0;
}

void main() {
	char* test = "1495033096 36:68:89:59:07:a5 192.168.1.224 * 01:36:68:89:59:07:a5";
	IPInfo ipInfo = readIPMac(test);
	printf("IP : %s\n", ipInfo.ip);
	printf("MAC : %s\n", ipInfo.mac);
	Info info;
	info.ipInfo = ipInfo;
	char* test2 = "36:68:89:59:07:A5  -39 dBm / unknown (SNR -39)  30 ms ago";
	info.rssiInfo.strength = getStrength(info.ipInfo.mac, test2);
	printf("strength : %d", info.rssiInfo.strength);
	free(info.ipInfo.ip);
	free(info.ipInfo.mac);
}
