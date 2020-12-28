
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
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	if (!newNode)
		return;

	newNode->data = Value;

	if (compare)
		L_insertSorted(head, newNode, compare);
	else
		L_insertByDefault(head, newNode);
}

void L_insertSorted(NODE** head, NODE* newNode, int(*compare)(void*, void*))
{
	NODE* temp;
	if ((*head)->data == NULL || compare(newNode->data, (*head)->data) < 0)
	{
		newNode->next = (*head);
		(*head) = newNode;
	}
	else
	{
		temp = (*head);
		while (temp->next != NULL && compare(newNode->data, temp->next->data) >= 0)
		{
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

void L_insertByDefault(NODE** head, NODE* newNode)
{
	NODE* temp;
	if ((*head)->data == NULL)
	{
		newNode->next = (*head);
		(*head) = newNode;
	}
	else
	{
		temp = (*head);
		while (temp->next!= NULL)
		{
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}

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

	NODE* temp = head;
	while (temp) 
	{
		if (temp->data)
			print(temp->data);
		temp = temp->next;
	}
	printf("\n");
}
