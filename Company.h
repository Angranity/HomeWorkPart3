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
int	saveToBinaryFile(Company* pComp);
int	readFromBinaryFile(Company* pComp);