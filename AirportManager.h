#pragma once
#include "Airport.h"
#include "listGen.h"

typedef struct
{
	NODE*	airportList;
	NODE	head;
	int			count;
}AirportManager;

int		initManager(AirportManager* pManager);
int		addAirport(AirportManager* pManager);
void	setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* p);
void	freeManager(void* p);
void 	saveToTextFile(AirportManager* pManager);
int 	readFromTextFile(AirportManager* pManager);