#pragma once
#include "Flight.h"
#include "AirportManager.h"

typedef enum
{
	eHourSort, eDateSort, eOriginCodeSort, eDestCodeSort, eNoSort
} eSortOptions;
typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	NODE*		dateList;
	NODE		head;
	eSortOptions sortOption;
}Company;

void	initCompany(Company* pComp);
int		addFlight(Company* pComp, const AirportManager* pManager);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	freeFlightArr(Flight** arr, int size);
void	freeCompany(Company* pComp);
void	saveToBinaryFile(Company* pComp);
int		readFromBinaryFile(Company* pComp);
void	freePtrFlight(Flight** flight);
void	printPtrFlight(const Flight** flight);
void	functionDate(Company* pComp, int i);
char*	fromDateToChar(Company* pComp, int i);
int		checkDateInList(Company* pComp, const char* date);
int		isSameDate(const char* date1, const char* date2);
void    sortFlight(Company *pComp);
void	printDateChar(const char* date);
int		compareByHour(const void* e1, const void* e2);
int		compareByDate(const void* e1, const void* e2);
int		compareByOriginCode(const void* e1, const void* e2);
int		compareByDestCode(const void* e1, const void* e2);
void	searchFlight(Company *pComp);