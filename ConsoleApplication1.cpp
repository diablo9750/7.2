// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <clocale>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "struct.h"


using namespace std;
using namespace types;

namespace types {
	// Сигнатуры требуемых внешних функций

	void Init(container &b);
	void Clear(container &b);
	game *InGame(game &g, ifstream &ifst);
	void OutGame(game *g, ofstream &ofst);
	cartoon *InCartoon(cartoon &c, ifstream &ifst);
	void OutCartoon(cartoon *c, ofstream &ofst);
	doc *InDoc(doc &d, ifstream &ifst);
	void OutDoc(doc *d, ofstream &ofst);
	void Out(film *f, ofstream &ofst);
	film *In(ifstream &ifst);
	int addlist(container &b, ifstream &ifst);
	void InContainer(container &b, ifstream &ifst);
	void Out(container &b, ofstream &ofst);
	int Vowel(game *g);
	int Vowel(cartoon *c);
	int Vowel(doc *d);
	int Vowel(film *f);
	bool Compare(film *first, film *second);
	void OutFilter(container &b, ofstream &ofst);
	void MultiMethod(container& c, ofstream& ofst);
}


void main(int argc, char* argv[])
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода 
	setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали

	ifstream ifst("in.txt");
	if (!ifst)
	{
		cout << "Wrong file input!" << endl;
		system("pause");
		exit(1);
	}
	ofstream ofst("out.txt", ios::trunc);

	/*if (argc != 3) {
	cout << "incorrect command line! "
	"Waited: command infile outfile" << endl;
	exit(1);
	}
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);*/
	cout << "Старт!" << endl;
	container b;
	Init(b);
	InContainer(b, ifst);
	ofst << "Контейнер заполнен. " << endl;
	Out(b, ofst);
	OutFilter(b, ofst);
	MultiMethod(b, ofst);
	Clear(b);
	ofst << "Контейнер пуст. " << endl;
	Out(b, ofst);
	cout << "Стоп." << endl;


	system("pause");

}


