#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	if (!L_init(&pManager->airportList))
		return 0;

	int count = 0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count); 
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;
	Airport* pA;
	pManager->pNode = &pManager->airportList.head;
	for (int i = 0; i < count; i++)
	{
		pA = (Airport*)malloc(sizeof(Airport));
		if (!pA)
			return 0;
		setAirport(pA, pManager);
		pManager->count++;
	}

	return 1;
}

int	addAirport(AirportManager* pManager)
{
	Airport* pA;
	pA = (Airport*)malloc(sizeof(Airport));
	if (!pA)
		return 0;
	setAirport(pA, pManager);
	pManager->count++;
	return 1;
}

void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
	pManager->pNode = L_insert(pManager->pNode, pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	NODE * temp = &pManager->airportList.head;
	while (temp)
	{
		if (isAirportCode(temp->key, code))
			return temp->key;
		temp = temp->next;
	}
	return NULL;
}

int checkUniqeCode(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(const void* p)
{
	const AirportManager* pManager = (const AirportManager*)p;
	printf("there are %d airports\n", pManager->count);
	printAirport(&pManager->airportList.head.key);
	printf("\n");
}

void	freeManager(void* p)
{
	free(p);
}
