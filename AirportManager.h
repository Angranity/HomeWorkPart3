#pragma once
#include "Airport.h"
#include "listGen.h"

typedef struct
{
	LIST	airportList;
	NODE*	pNode;
	int			count;
}AirportManager;

int		initManager(AirportManager* pManager);
int		addAirport(AirportManager* pManager);
void	setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const void* p);
void	freeManager(void* p);