#pragma once
#define MAX_STR_LEN 255
#define CODE_LENGTH 3

char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void generalArrayFunction(const void* arr, int size, int typeSize, void(*function)(const void*));


