#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"

const char* sort[eNoSort] = { "Sort by hour", "Sort by date",
								"Sort by origin code", "Sort by dest code" };

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->dateList = L_init();
	pComp->head = *pComp->dateList;
	pComp->sortOption = eNoSort;
}

int	addFlight(Company* pComp, const AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount], pManager);
	pComp->flightCount++;
	return 1;
}

void printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}



void	printFlightArr(Flight** pFlight, int size)
{
	for (int i = 0; i < size; i++)
		printFlight(pFlight[i]);
}

void	freeFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
}

void	freeCompany(Company* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
}

int	saveToBinaryFile(Company* pComp) {
	int i;
	size_t nameLength;
	FILE* f = fopen("company.bin", "wb");
	if (!f)
		return 0;

	nameLength = strlen(pComp->name) + 1;
	fwrite(&nameLength, sizeof(int), 1, f);
	fwrite(pComp->name, sizeof(char), nameLength, f);
	fwrite(&(pComp->flightCount), sizeof(int), 1, f);
	fwrite(&(pComp->sortOption), sizeof(int), 1, f);

	for (i = 0; i < pComp->flightCount; i++) {
		fwrite(pComp->flightArr[i]->originCode, sizeof(char), CODE_LENGTH + 1, f);
		fwrite(pComp->flightArr[i]->destCode, sizeof(char), CODE_LENGTH + 1, f);
		fwrite(&(pComp->flightArr[i]->hour), sizeof(int), 1, f);
		fwrite(&pComp->flightArr[i]->date.day, sizeof(int), 1, f);
		fwrite(&pComp->flightArr[i]->date.month, sizeof(int), 1, f);
		fwrite(&pComp->flightArr[i]->date.year, sizeof(int), 1, f);
	}

	fclose(f);
	return 1;
}

int	readFromBinaryFile(Company* pComp) {
	int i, nameLength;
	FILE* f = fopen("company.bin", "rb");
	if (!f)
		return 0;

	fread(&nameLength, sizeof(int), 1, f);
	pComp->name = (char*)malloc(nameLength * sizeof(char));
	if (!pComp->name)
		return 0;
	fread(pComp->name, sizeof(char), nameLength, f);

	fread(&(pComp->flightCount), sizeof(int), 1, f);

	fread(&(pComp->sortOption), sizeof(int), 1, f);
	pComp->flightArr = NULL;
	pComp->dateList = L_init();
	pComp->head = *pComp->dateList;

	for (i = 0; i < pComp->flightCount; i++) {
		pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		fread(pComp->flightArr[i]->originCode, sizeof(char), CODE_LENGTH + 1, f);
		fread(pComp->flightArr[i]->destCode, sizeof(char), CODE_LENGTH + 1, f);
		fread(&(pComp->flightArr[i]->hour), sizeof(int), 1, f);
		fread(&pComp->flightArr[i]->date.day, sizeof(int), 1, f);
		fread(&pComp->flightArr[i]->date.month, sizeof(int), 1, f);
		fread(&pComp->flightArr[i]->date.year, sizeof(int), 1, f);
	}

	fclose(f);
	return 1;
}