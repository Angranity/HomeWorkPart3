#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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
	functionDate(pComp, pComp->flightCount);
	pComp->flightCount++;
	return 1;
}

void	functionDate(Company* pComp, int i)
{
	char* date;
	date = fromDateToChar(pComp, i);
	if (checkDateInList(pComp, date))
		L_insert(&(pComp->dateList), date, NULL);
}

int		checkDateInList(Company* pComp, const char* date)
{
	NODE* temp = pComp->dateList;
	while (temp)
	{
		if (isSameDate(temp->data, date) == 0)
			return 0;
		temp = temp->next;
	}
	return 1;
}
int		isSameDate(const char* date1, const char* date2)
{
	if (!date1)
		return 1;
	if (strcmp(date1, date2) == 0)
		return 0;
	return 1;
}

char*	fromDateToChar(Company* pComp, int i)
{
	char temp[MAX_STR_LEN] = "";
	char day[3];
	char month[3];
	char year[5];
	_itoa(pComp->flightArr[i]->date.day, day, 10);
	strcat(temp, day);
	strcat(temp, "/");
	_itoa(pComp->flightArr[i]->date.month, month, 10);
	strcat(temp, month);
	strcat(temp, "/");
	_itoa(pComp->flightArr[i]->date.year, year, 10);
	strcat(temp, year);
	char * temp2 = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
	if (!temp2)
		return NULL;
	strcpy(temp2, temp);
	return temp2;
}

void printCompany(const Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
	printf("\nFlight Date List:\n");
	L_print(pComp->dateList, printDateChar);
}
void	printDateChar(const char* date)
{
	printf("Date: %s\n", date);
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
	generalArrayFunction(pFlight, size, sizeof(*pFlight), printPtrFlight);
}

void printPtrFlight(const Flight** flight)
{
	printFlight(*flight);
}

void	freeFlightArr(Flight** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(*arr), freePtrFlight);
}

void freePtrFlight(Flight** flight)
{
	freeFlight(*flight);
}

void	freeCompany(Company* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->head, NULL);
}

int	saveToBinaryFile(Company* pComp) {
	int i;
	size_t nameLength;
	FILE* f = fopen("company.bin", "wb");
	if (!f)
		return 0;

	nameLength = strlen(pComp->name) + 1;
	if (fwrite(&nameLength, sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(pComp->name, sizeof(char), nameLength, f) != nameLength)
		return 0;
	if (fwrite(&(pComp->flightCount), sizeof(int), 1, f) != 1)
		return 0;
	if (fwrite(&(pComp->sortOption), sizeof(int), 1, f) != 1)
		return 0;

	for (i = 0; i < pComp->flightCount; i++) {
		if (fwrite(pComp->flightArr[i], sizeof(Flight), 1, f) != 1)
			return 0;
	}

	fclose(f);
	return 1;
}

int	readFromBinaryFile(Company* pComp) {
	int i, nameLength;
	FILE* f = fopen("company.bin", "rb");
	if (!f)
		return 0;

	if (fread(&nameLength, sizeof(int), 1, f) != 1)
		return 0;
	pComp->name = (char*)malloc(nameLength * sizeof(char));
	if (!pComp->name)
		return 0;
	if (fread(pComp->name, sizeof(char), nameLength, f) != nameLength)
		return 0;

	if (fread(&(pComp->flightCount), sizeof(int), 1, f) != 1)
		return 0;

	if (fread(&(pComp->sortOption), sizeof(int), 1, f) != 1)
		return 0;
	pComp->flightArr = NULL;
	pComp->dateList = L_init();
	pComp->head = *pComp->dateList;

	for (i = 0; i < pComp->flightCount; i++) {
		pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
		if (!pComp->flightArr)
			return 0;
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		if (!pComp->flightArr[i])
			return 0;
		if (fread(pComp->flightArr[i], sizeof(Flight), 1, f) != 1)
			return 0;
		functionDate(pComp, i);
	}

	fclose(f);
	return 1;
}

void    sortFlight(Company *pComp)
{
	int option;
	printf("\n\n");
	printf("Base on what field do you want to sort?\n");
	for (int i = 0; i < eNoSort; i++)
		printf("Enter %d for %s\n", i + 1, sort[i]);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	switch (option - 1)
	{
	case eHourSort:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByHour);
		pComp->sortOption = eHourSort;
		break;


	case eDateSort:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDate);
		pComp->sortOption = eDateSort;
		break;

	case eOriginCodeSort:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByOriginCode);
		pComp->sortOption = eOriginCodeSort;
		break;

	case eDestCodeSort:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDestCode);
		pComp->sortOption = eDestCodeSort;
		break;

	default:
		printf("Wrong option\n");
		break;
	}
}


int		compareByHour(const void* e1, const void* e2)
{
	const Flight* flight1 = *(const Flight**)e1;
	const Flight* flight2 = *(const Flight**)e2;
	return flight1->hour - flight2->hour;
}
int		compareByDate(const void* e1, const void* e2)
{
	const Flight* flight1 = *(const Flight**)e1;
	const Flight* flight2 = *(const Flight**)e2;

	if (flight1->date.day == flight2->date.day && flight1->date.month == flight2->date.month && flight1->date.year == flight2->date.year)
		return 0;
	else if (flight1->date.year > flight2->date.year || flight1->date.year == flight2->date.year && flight1->date.month > flight2->date.month ||
		flight1->date.year == flight2->date.year && flight1->date.month == flight2->date.month && flight1->date.day > flight2->date.day)
		return 1;
	else return -1;
}
int		compareByOriginCode(const void* e1, const void* e2)
{
	const Flight* flight1 = *(const Flight**)e1;
	const Flight* flight2 = *(const Flight**)e2;
	return strcmp(flight1->originCode, flight2->originCode);
}
int		compareByDestCode(const void* e1, const void* e2)
{
	const Flight* flight1 = *(const Flight**)e1;
	const Flight* flight2 = *(const Flight**)e2;
	return strcmp(flight1->destCode, flight2->destCode);
}

void	searchFlight(Company *pComp)
{
	Flight* tempFlight = (Flight*)malloc(sizeof(Flight));
	if (!tempFlight)
		return;
	Flight* pFound = NULL;
	switch (pComp->sortOption)
	{
	case eHourSort:
	{
		tempFlight->hour = getFlightHour();
		pFound = bsearch(&tempFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByHour);
		break;
	}

	case eDateSort:
		getCorrectDate(&(tempFlight->date));
		pFound = bsearch(&tempFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDate);
		break;

	case eOriginCodeSort:
		getAirportCode((tempFlight->originCode));
		pFound = bsearch(&tempFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByOriginCode);
		break;

	case eDestCodeSort:
		getAirportCode((tempFlight->destCode));
		pFound = bsearch(&tempFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDestCode);
		break;

	case eNoSort:
		printf("The search cannot be performed, array not sorted");
		break;

	default:
		printf("Wrong option\n");
		break;
	}
	if (!pFound)
		printf("Flight was not found");
	else
	{
		printf("Flight Found, ");
		printFlight(*(Flight**)pFound);
	}
	free(tempFlight);
}