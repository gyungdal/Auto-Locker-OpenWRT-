#include "list.h"
#define DEBUG 1

static Item head, tail;

Item listInit() {
	Item item = (Item)malloc(sizeof(Item));
	item->name = NULL;
	item->type = 2;
	item->next = NULL;
	printf("INIT ITEM\n");
	return item;
}

void listRelease(Item item) {
	while (item != NULL) {
		item = item->next;
		free(item->name);
		free(item);
	}
}

void listAdd(Item item, char* name, int type) {
	Item backup = item;
	if(item->name == NULL){
		tail = head = item;
		item->name = name;
		item->type = type;
	}else{
		printf("%s\n", tail->name);
		tail->next = (Item)malloc(sizeof(Item));
		tail->next->name = name;
		tail->next->type = type;
		tail->next->next = NULL;
		tail = tail->next;
		printf("%s\n", (tail != NULL ? "OK" : "WTF?"));
		printf("%s\n", tail->name);
	}
	item = backup;
}

void listPrint(Item item) {
	Item backup = item;
	while (item != NULL) {
		printf("Name : %s\tType : %s\n", item->name, (item->type == 0 ? "FILE" : "FOLDER"));
		item = item->next;
	}
	item = backup;
}
