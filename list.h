#pragma once
#include <stdio.h>
#include <stdlib.h>


typedef struct I* Item;
struct I {
	char* name;
	int type;
	Item next;
};

Item listInit();
void listRelease(Item);
void listAdd(Item, char*, int);
void listPrint(Item);
