
#include <stdio.h>
#include <stdlib.h>
#include "listGen.h"


NODE* L_init()
{
	NODE* head = (NODE*)malloc(sizeof(NODE));
	if (!head)
		return NULL;

	head->data = NULL;
	head->next = NULL;
	return head;
}


void L_insert(NODE** head, void* Value, int(*compare)(void*, void*))
{
	NODE* temp = *head;
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if (!newNode)
		return;
	newNode->data = Value;
	if (compare!=NULL)
	{
		while (temp->next && compare(newNode->data, temp->next->data) >= 0)
			temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
}

void L_delete(NODE* head, void(*freeFunc)(void*))
{
	NODE* tmp;

	if (!head || !(tmp = head->next)) return;

	head->next = tmp->next;
	if (freeFunc != NULL)
		freeFunc(tmp->data);
	free(tmp);
}


void L_free(NODE* head, void(*freeFunc)(void*))
{
	NODE *tmp = NULL;
	NODE *pNode = head;

	if (!pNode) return;

	while (pNode)
	{
		tmp = pNode;
		pNode = pNode->next;
		L_delete(tmp, freeFunc);
	}
}


void L_print(NODE* head, void(*print)(const void*))
{
	if (!head)
		return;

	NODE* temp = head->next;
	while (temp)
	{
		if (temp->data)
			print(temp->data);
		temp = temp->next;
	}
	printf("\n");
}
