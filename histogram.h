#pragma once

//Структура для описания гисторгаммы
typedef struct {
	char **BarNames;
	int *Bars;
	int nBarsSize;
	char chBlock;
	int nMaxBar;
} Histogram;

// Структура для сортировки
typedef struct {
	char *BarName;
	int BarSize;
} Temporary;

//Функции для работы с гисторгаммой
void inline InitHistogram(Histogram &historgam);
void inline DestroyHistogram(Histogram &historgam);
void PrintHistogram(const Histogram &historgam);
void AddBlock(Histogram &historgam, const char *strName);
void SortByName(Histogram &histogram, bool bAscending);
void Frequency(Histogram &histogram, char *str);
void CreateHistogram(Histogram &histogram, char *str);
int MaxBarLength(const Histogram &histogram);
bool AscComparator(const Temporary a, const Temporary b);
bool DescComparator(const Temporary a, const Temporary b);
int Input();
char *InputString();
char *SuppFunc(char *str);
void Sep();
#include "histogram.inl"
