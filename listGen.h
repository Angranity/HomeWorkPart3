#pragma once

typedef struct NODE {
	void* data;
	struct NODE* next;
} NODE;


/*** Function prototypes ***/

NODE* L_init();					// create new list

void L_insert(NODE** head, void* Value, int(*compare)(void*, void*));	// add new node after *pNode

void L_insertSorted(NODE** head, NODE* newNode, int(*compare)(void*, void*));

void L_insertByDefault(NODE** head, NODE* newNode);

void L_delete(NODE* head, void(*freeFunc)(void*));					// erase node after *pNode

void L_free(NODE* head, void(*freeFunc)(void*));					// free list memory

void L_print(NODE* head, void(*print)(const void*));					// print the list content
