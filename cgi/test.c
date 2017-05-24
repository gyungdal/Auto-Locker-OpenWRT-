#include "list.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

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
	char* mac;
	char* ip;
	char* name;
	int strength;
} TotalInfo;

typedef struct listItem listItem;

struct listItem{
	void* item;
	listItem* next;
};

MacInfo* getStrength(char*);
listItem* readIPMac(char*);
listItem* readMacInfo(char*);
listItem* getTotalInfo(listItem*,listItem*);

listItem* readIPMac(char* fileName){
	FILE* fp = fopen(fileName, "r");
	char* temp = (char*)malloc(sizeof(char) * 256);
	listItem* items = (listItem*)malloc(sizeof(listItem*));
	listItem* tail;
	items->item = NULL;
	items->next = NULL;
	while(fgets(temp, 256, fp) != NULL){
		char* ip = (char*)malloc(sizeof(char) * 20);
		char* mac = (char*)malloc(sizeof(char) * 20);
		sscanf(temp, "%*s %s %s %*s %*s", mac, ip);
		IPInfo* info = (IPInfo*)malloc(sizeof(IPInfo*));
		info->ip = ip;
		info->mac = mac;
		if(items->item == NULL){
			items->item = info;
			tail = items;
		}else{
			tail->next = (listItem*)malloc(sizeof(listItem*));
			tail->next->item = info;
			tail = tail->next;
			tail->next = NULL;
		}
	}
	fclose(fp);
	free(temp);
	return items;
}

listItem* readMacInfo(char* fileName){
	FILE* fp = fopen(fileName, "r");
	char* temp = (char*)malloc(sizeof(char) * 256);
	listItem* items = (listItem*)malloc(sizeof(listItem*));
	listItem* tail;
	items->item = NULL;
	items->next = NULL;
	while(fgets(temp, 256, fp) != NULL){
	printf("dd");
		if(strstr(temp, "ms") != NULL){
			printf("DEBUG : %s\n", temp);
			MacInfo* info = getStrength(temp);
			printf("INFO!\n");
			if(items->item == NULL){
				items->item = info;
				tail = items;
			}else{
				tail->next = (listItem*)malloc(sizeof(listItem*));
				tail->next->item = info;
				tail = tail->next;
				tail->next = NULL;
			}
		}
		memset(temp, 0x00, 256);
	}
	fclose(fp);
	free(temp);
	return items;
}

MacInfo* getStrength(char* str){
	printf(str);
	MacInfo* info = (MacInfo*)malloc(sizeof(MacInfo*));
	info->mac = (char*)malloc(sizeof(char) * 20);
	info->name = (char*)malloc(sizeof(char) * 1024);
	if(info->mac == NULL | info->name == NULL){
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	//36:68:89:59:07:A5  -39 dBm / GyungDal (SNR -39)  30 ms ago
	sscanf(str, "%s %d %*s %*s %s ", info->mac, &info->strength, info->name);
	#if DEBUG
		printf("%s\n", info->name);
		printf("%s\n", info->mac);
		printf("%d\n", info->strength);
	#endif
	return info;
}

listItem* getTotalInfo(listItem* ips, listItem* macs){
	listItem* items = (listItem*)malloc(sizeof(listItem*));
	listItem* tail;
	listItem* temp = macs;
	items->item = items->next = NULL;
	while(ips->next != NULL){
		macs = temp;
		while(macs->next != NULL){
			IPInfo* ip = (IPInfo*)ips->item;
			MacInfo* mac = (MacInfo*)macs->item;
			printf("%s\n", ip->mac);
			printf("%s\n", mac->mac);
			if(strncasecmp(ip->mac, mac->mac, strlen(mac->mac) - 1) == 0){
				printf("!!!\n");
				TotalInfo* info = (TotalInfo*)malloc(sizeof(TotalInfo*));
				info->mac = ip->mac;
				info->ip = ip->ip;
				info->name = mac->name;
				info->strength = mac->strength;
				free(ip);
				if(items->item == NULL){
					items->item = info;
					tail = items;
				}else{
					tail->next = (listItem*)malloc(sizeof(listItem*));
					tail->next->item = info;
					tail = tail->next;
					tail->next = NULL;
				}
			}
		}
		listItem* a = ips->next;
		free(ips);
		free(ips->item);
		a = ips;
	}
	macs = temp;
	while(macs->next != NULL){
		listItem* temp = macs->next;
		MacInfo* mac = (MacInfo*)macs->item;
		free(mac->mac);
		free(mac);
		free(macs);
		macs = temp;
	}
	return items;
}

void main() {
	listItem* IPs = readIPMac("test");
	while(IPs != NULL){
		IPInfo* info = (IPInfo*)IPs->item;
		printf("============\n");
		printf("IP : %s\n", info->ip);
		printf("MAC : %s\n", info->mac);
		printf("\n\n");
		IPs = IPs->next;
	}
	listItem* MACs = readMacInfo("test2");
	while(MACs != NULL){
		MacInfo* info = (MacInfo*)MACs->item;
		printf("============\n");
		printf("MAC : %s\n", info->mac);
		printf("NAME : %s\n", info->name);
		printf("POWER : %d\n", info->strength);
		printf("\n\n");
		MACs = MACs->next;
	}
	listItem* Totals = getTotalInfo(IPs, MACs);
	while(Totals != NULL){
		TotalInfo* info = (TotalInfo*)Totals->item;
		printf("====== TOTAL ======\n");
		printf("NAME : %s\n", info->name);
		printf("IP : %s\n", info->ip);
		printf("MAC : %s\n", info->mac);
		printf("POWER : %s\n", info->strength);
		printf("\n\n");
		Totals = Totals->next;
	}

}
