#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	pManager->airportList = L_init();
	pManager->head = *pManager->airportList;
	if (!pManager->airportList)
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

	for (int i = 0; i < count; i++)
	{
		addAirport(pManager);
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
	L_insert(&(pManager->airportList), pA, compareByABC);
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
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	NODE * temp = pManager->airportList;
	while (temp)
	{
		if (isAirportCode(temp->data, code))
			return temp->data;
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

void	printAirports(const AirportManager* p)
{
	printf("there are %d airports\n", p->count);
	L_print(p->airportList, printAirport);
	printf("\n");
}
void	saveToTextFile(AirportManager* pManager)
{
	int i;
	Airport* airport;
	NODE* temp = pManager->airportList;

	FILE* f = fopen("airport_authority.txt", "w");
	if (!f)
		return;

	fprintf(f, "%d\n", pManager->count);

	for (i = 0; i < pManager->count; i++) {
		airport = (Airport*)(temp->next->data);
		fprintf(f, "%s\n", airport->name);
		fprintf(f, "%s\n", airport->country);
		fprintf(f, "%s\n", airport->code);
		temp = temp->next;
	}

	fclose(f);
}

int	readFromTextFile(AirportManager* pManager)
{
	Airport* airport;
	FILE* f = fopen("airport_authority.txt", "r");
	if (!f)
		return 0;
	pManager->airportList = L_init();
	pManager->head = *pManager->airportList;
	fscanf(f, "%d\n", &(pManager->count));

	char tempName[MAX_STR_LEN];
	char tempCountry[MAX_STR_LEN];
	for (int i = 0; i < pManager->count; i++)
	{
		airport = (Airport*)malloc(sizeof(Airport));
		if (!airport)
			return 0;
		fgets(tempName, MAX_STR_LEN, f);
		tempName[strlen(tempName) - 1] = '\0';
		airport->name = _strdup(tempName);
		fgets(tempCountry, MAX_STR_LEN, f);
		tempCountry[strlen(tempCountry) - 1] = '\0';
		airport->country = _strdup(tempCountry);
		fscanf(f, "%s\n", &airport->code);
		L_insert(&pManager->airportList, airport, compareByABC);
	}

	fclose(f);
	return 1;
}

void	freeManager(void* p)
{
	free(p);
}
