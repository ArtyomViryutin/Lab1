#include "histogram.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <locale>


int main() {

	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");

	const char * const strProgramName = "Histogramer 1.0";
	std::cout << std::setfill('*') << std::setw(strlen(strProgramName) + 4) << "" << std::endl;
	std::cout << '*' << std::setfill(' ') << std::setw(strlen(strProgramName) + 3) << '*' << std::endl;
	std::cout << "* " << strProgramName << " *" << std::endl;
	std::cout << '*' << std::setfill(' ') << std::setw(strlen(strProgramName) + 3) << '*' << std::endl;
	std::cout << std::setfill('*') << std::setw(strlen(strProgramName) + 4) << "" << std::endl << std::endl;

	Histogram myBarChart;
	InitHistogram(myBarChart);

	std::cout << "Выберите действие:\n" << "1 - Выполнение по умолчанию\n" << "2 - Ввод строки с клавиатуры\n" << "0 - Выход из программы\n" << "Ваш выбор: ";
	int N = Input();
	switch (N) {
	case 1:
		AddBlock(myBarChart, "a");
		AddBlock(myBarChart, "a");
		AddBlock(myBarChart, "c");
		AddBlock(myBarChart, "d");
		AddBlock(myBarChart, "e");
		AddBlock(myBarChart, "r");
		AddBlock(myBarChart, "a");
		AddBlock(myBarChart, "b");
		AddBlock(myBarChart, "b");
		break;
	case 2:
		char *String; // Строка для ввода
		Histogram NewBarChart; // Структура для гистограммы частоты встречающихся строчных букв
		InitHistogram(NewBarChart);
		Sep();
		std::cout << "Введите строку:" << std::endl;
		String = InputString(); // Ввод строки
		Frequency(NewBarChart, String); // Заполнение гистограммы
		CreateHistogram(myBarChart, String); // Создание гистограммы частоты встречающихся слов в строке
		Sep();
		std::cout << "Гистограмма частоты строчных букв:" << std::endl;
		if (NewBarChart.nMaxBar == 0) // Условие на случай, если в строке все различные слова встречаются один раз
			NewBarChart.nMaxBar = 1;
		PrintHistogram(NewBarChart);
		Sep();
		DestroyHistogram(NewBarChart);
		delete[] String;
		break;
	case 0:
		exit(0);
		break;
	}


	std::cout << "Выберите способ сортировки:\n" << "1 - По возрастанию\n" << "2 - По убыванию\n" << "0 - Я не хочу сортировать\n" << "Ваш выбор: ";
	N = Input();
	Sep();
	switch (N) {
	case 1:
		SortByName(myBarChart, true);
		break;
	case 2:
		SortByName(myBarChart, false);
		break;
	case 0:
		break;
	}

	if (myBarChart.nMaxBar == 0)
		myBarChart.nMaxBar = 1;
	PrintHistogram(myBarChart);

	DestroyHistogram(myBarChart);

	system("pause");
	return 0;
}
