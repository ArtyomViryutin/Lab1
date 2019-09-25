#define _CRT_SECURE_NO_WARNINGS
#include "histogram.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

///////////////////////////////////////////////////////////////////
// Вспомогательные функции
void AddBar(Histogram &historgam, const char *strName);
bool AppendBar(Histogram &historgam, const char *strName);

///////////////////////////////////////////////////////////////////
// реализация функций из файла histogram.h


//-----------------------------------------------------------------
// Функция Input осуществляет ввод числа для оператора выбора switch и проверяет корректность ввода
int Input() {
	int n;
	while (!(std::cin >> n) or n != 1 and n != 2 and n != 0 or getchar() != '\n') {
		cout << "Такого действия не существует.Попробуйте ввести еще раз: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return n;
}
// *** 4 ***
// Функция MaxBarLenght ищет длину наибольшего имя из имен столбцов гистограммы
// и передает его значение в функцию PrintHistogram для корректной работы, если имена столбцов имеют разную длину
int MaxBarLength(const Histogram &histogram) {
	int max = 1;
	for (int i = 0; i < histogram.nBarsSize; i++) {
		if (strlen(histogram.BarNames[i]) > max)
			max = strlen(histogram.BarNames[i]);
	}
	return max;
}

// Функция AddBlock увеличивает значение столбца strName гистограмы historgam на 1.
// Если столбца с таким именем не существует, он создается.
void AddBlock(Histogram &historgam, const char *strName) {
	if (!AppendBar(historgam, strName)) {
		AddBar(historgam, strName);
	}
}

//-----------------------------------------------------------------
// Функция PrintHistogram выводит гистограму на экран.
void PrintHistogram(const Histogram &historgam) {
	for (int i = 0; i < historgam.nBarsSize; i++) {
		cout << setfill(' ') << setw(MaxBarLength(historgam)) << historgam.BarNames[i] << '|';
		cout << setfill(historgam.chBlock) << setw(10 * historgam.Bars[i] / historgam.nMaxBar) << "" << ends << endl;
	}
}

///////////////////////////////////////////////////////////////////
// реализация вспомогательных функций
//Функция InputString осуществляет ввод строки типа char и возвращает указатель на нее
char *InputString() {
	char* str = new char[1];
	char c = getchar();
	int k = 1;
	while (c != '\n') {
		str = (char*)realloc(str, k + 1);
		str[k - 1] = c;
		c = getchar();
		k++;
	}
	str[k - 1] = '\0';
	return str;
}
// Компоратор для функции sort для сортировки по возрастанию
bool AscComparator(const Temporary a, const Temporary b) {
	if (strcmp(a.BarName, b.BarName) <= 0)
		return false;
	else
		return true;
}
// Компоратор для функции sort для сортировки по убыванию
bool DescComparator(const Temporary a, const Temporary b) {
	if (strcmp(a.BarName, b.BarName) <= 0)
		return true;
	else
		return false;
}
// *** 1 ***
// Функция для сортировки столбцов гистограммы по имени столбца в алфавитном порядке
void SortByName(Histogram &histogram, bool bAscending) {
	Temporary* Sorting = new Temporary[histogram.nBarsSize]; // Массив структур для сортировки
	for (int i = 0; i < histogram.nBarsSize; i++) {
		Sorting[i].BarName = histogram.BarNames[i]; // Присваивание имен столбцов в массив структур
		Sorting[i].BarSize = histogram.Bars[i]; 
	}
	if (bAscending) {
		sort(Sorting, Sorting + histogram.nBarsSize, AscComparator); // Сортировка по возрастанию в случае, если bAscending = true
	}
	else {
		sort(Sorting, Sorting + histogram.nBarsSize, DescComparator); // Сортировка по убыванию в случае, если bAscending = false
	}

	for (int i = 0; i < histogram.nBarsSize; i++) {
		histogram.BarNames[i] = Sorting[i].BarName; // Присваивание структуре гистограммы сортированных имен
		histogram.Bars[i] = Sorting[i].BarSize;
	}
	delete[] Sorting; 
}
// Функция для передачи символов в функцию AddBlock
char *SuppFunc(char *str) {
	char *c = new char[2];
	c[0] = *str;
	c[1] = '\0';
	return c;
}
// *** Е ***
// Функция, иллюстрирующей частоту встречающихся строчных букв латинского алфавита
void Frequency(Histogram &histogram, char *str)
{
	for (int i = 0; i < strlen(str); i++) {
		if (96 < str[i] and str[i] < 123) {
			AddBlock(histogram, SuppFunc(str + i));
		}
	}
	SortByName(histogram, false); // Сортировка по убыванию
}
// Функция создания гистограммы частоты встречающихся слов в передаваемой стркое
void CreateHistogram(Histogram &histogram, char *str) {
	char Separators[] = " ,.;:!?-";
	char *temp = strtok(str, Separators);
	while (temp != NULL) {
		AddBlock(histogram, temp);
		temp = strtok(NULL, Separators);
	}
}

void Sep() {
	cout << "----------------------------------------\n";
}



//-----------------------------------------------------------------
// Функция AppendBar увеличивает значение столбца strName гистограмы historgam на 1.
bool AppendBar(Histogram &historgam, const char *strName) {
	for (int i = 0; i < historgam.nBarsSize; i++) {
		if (strcmp(historgam.BarNames[i], strName) == 0) {
			historgam.nMaxBar = max(historgam.nMaxBar, ++historgam.Bars[i]);
			return true;
		}
	}
	return false;
}

// Функция AddBar создает в гистограме historgam новый столбец с именем strName.
//-----------------------------------------------------------------
void AddBar(Histogram &historgam, const char *strName) {
	char **newNames = new char *[historgam.nBarsSize + 1];
	int   *newBars = new int[historgam.nBarsSize + 1];
	if (historgam.nBarsSize > 0) {
		for (int i = 0; i < historgam.nBarsSize; i++) {
			newNames[i] = historgam.BarNames[i];
			newBars[i] = historgam.Bars[i];
		}
		delete[] historgam.BarNames;
		delete[] historgam.Bars;
	}

	newNames[historgam.nBarsSize] = new char[strlen(strName) + 1];
	strcpy(newNames[historgam.nBarsSize], strName);
	newBars[historgam.nBarsSize] = 1;

	historgam.nBarsSize++;
	historgam.BarNames = newNames;
	historgam.Bars = newBars;
}
