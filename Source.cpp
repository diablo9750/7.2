#include "stdafx.h"
#include "struct.h" 
#include <fstream>
#include <iostream>

using namespace std;

namespace types {
	bool isdigit(int int_test)
	{
		int mass[10] = { { 0 }, { 1 },{ 2 }, { 3 }, { 4 }, { 5 }, { 6 }, { 7 }, { 8 }, { 9 } };
		for (int i = 0; i < 10; i++)
		{
			if (int_test == mass[i])
			{
				return true;
			}
		}
		return false;
	}
	//--------------------------------------------------
	//Дополнительные функции

	//Расчёт количества гласных
	int Vowel(game *g) {
		int count = 0;
		char mass[] = { "аеоуияэыёАЁОУИЯЭЫЁ" };
		for (int i = 0; i < strlen(g->name); i++)
		{
			for (int j = 0; j < strlen(mass); j++)
			{
				if (g->name[i] == mass[j])
				{
					count++;
				}
			}
		}
		return count;
	}

	int Vowel(cartoon *c) {
		int count = 0;
		char mass[] = { "аеоуияэыёАЁОУИЯЭЫЁ" };
		for (int i = 0; i < strlen(c->name); i++)
		{
			for (int j = 0; j < strlen(mass); j++)
			{
				if (c->name[i] == mass[j])
				{
					count++;
				}
			}
		}
		return count;
	}

	int Vowel(doc *d) {
		int count = 0;
		char mass[] = { "аеоуияэыёАЁОУИЯЭЫЁ" };
		for (int i = 0; i < strlen(d->name); i++)
		{
			for (int j = 0; j < strlen(mass); j++)
			{
				if (d->name[i] == mass[j])
				{
					count++;
				}
			}
		}
		return count;
	}

	int Vowel(film *f)
	{
		switch (f->key)
		{
		case GAME:
		{
			return Vowel((game*)f);
		}break;
		case CARTOON:
		{
			return Vowel((cartoon*)f);
		}break;
		case DOC:
		{
			return Vowel((doc*)f);
		}break;
		default:
		{
			return -1;
		}break;
		}
	}

	//Сортировка по ключу
	bool Compare(film *first, film *second) {
		return Vowel(first) > Vowel(second);
	}

	void Sort(container &b)
	{
		List* current = b.Top;
		if (b.count > 1)
		{
			for (int j = 1; j < b.count; j++)
			{
				if (Compare(current->data, current->Next->data))
				{
					List p;
					p.data = current->data;
					current->data = current->Next->data;
					current->Next->data = p.data;
					j = 0;
					current = b.Top;
				}
				else
				{
					current = current->Next;
				}
		}
		
		}
	}

	//--------------------------------------------------

	// Ввод параметров игрового фильма из файла
	game *InGame(game &g, ifstream &ifst) {
		ifst >> g.country >> g.name >> g.director;
		return &g;
	}

	// Вывод параметров игрового фильма в поток
	void OutGame(game *g, ofstream &ofst) {
		ofst << "Это игровой фильм. Страна, где произведён фильм: " << g->country << ", Название фильма: " << g->name
			<< ", Режиссёр: " << g->director << endl;
	}

	//--------------------------------------------------

	// Ввод параметров мультфильма из потока
	cartoon *InCartoon(cartoon &c, ifstream &ifst)
	{
		ifst >> c.country >> c.name >> c.type;
		return &c;
	}

	// Вывод параметров мультфильма в поток
	void OutCartoon(cartoon *c, ofstream &ofst)
	{
		ofst << "Это мультильм. Страна, где произведён фильм: " << c->country << ", Название фильма: " << c->name << ", вид мультфильма: ";

		if (c->type == 1) {
			ofst << "рисованный" << endl;
		}
		if (c->type == 2) {
			ofst << "кукольный" << endl;
		}
		if (c->type != 1 && c->type != 2) {
			ofst << "Неизвестный вид мультфильма" << endl;
		}
	}

	//--------------------------------------------------

	// Ввод параметров документального фильма из файла
	doc *InDoc(doc &d, ifstream &ifst) {
		ifst >> d.country >> d.name >> d.date;
		return &d;
	}

	// Вывод параметров игрового фильма в поток
	void OutDoc(doc *d, ofstream &ofst) {
		ofst << "Это доументальный фильм.Страна, где произведён фильм: " << d->country << ", Название фильма: " << d->name << ", Год выпуска: " << d->date << endl;
	}

	//--------------------------------------------------

	//Вывод по ключу
	void Out(film *f, ofstream &ofst) {
		switch (f->key)
		{
		case 1:
		{
			OutGame((game*)f, ofst);
		}break;
		case 2:
		{
			OutCartoon((cartoon*)f, ofst);
		}break;
		case 3:
		{
			OutDoc((doc*)f, ofst);
		}break;
		default:
		{
			cout << "Некорректный фильм!" << endl;
		}break;
		}
	}

	// Ввод параметров обобщенного фильма из файла
	film *In(ifstream &ifst)
	{
		film *fm = new film;
		int k;
		ifst >> k;
		if(!isdigit(k))
		{
			cout << "Неверный ключ!" << endl;
			exit(1);
		}
		if (k == 1) {
			game *g = new game;
			fm = (film*)InGame(*g, ifst);
			fm->key = GAME;
			return fm;
		}
		if (k == 2)
		{
			cartoon *c = new cartoon;
			fm = (film*)InCartoon(*c, ifst);
			fm->key = CARTOON;
			return fm;
		}
		if (k == 3) {
			doc *d = new doc;
			fm = (film*)InDoc(*d, ifst);
			fm->key = DOC;
			return fm;
		}
		if (k < 1 || k>3)
		{
			cout << "Неверный ключ!" << endl;
			exit(1);
			return 0;
		}
	}

	//--------------------------------------------------

	// Инициализация контейнера
	void Init(container &b) {
		b.Top = nullptr;
		b.count = 0;
	}

	//Добавление узла списка
	int addlist(container &b, ifstream &ifst)
	{
		//Если контейнер пустой
		if (b.count == 0)
		{
			b.Top = new List;
			if ((b.Top->data = In(ifst)) != 0)
				return 1;
			else
				return 0;

		}
		else
		{
			List *current = b.Top;
			for (int j = 0; j < b.count - 1; j++)
			{
				current = current->Next;
			}
			current->Next = new List;
			if ((current->Next->data = In(ifst)) != 0)
			{
				b.Top->Priv = current->Next;
				current->Next->Priv = current;
				current->Next->Next = b.Top;
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	// Ввод содержимого контейнера из указанного потока
	void InContainer(container &b, ifstream &ifst) {
		while (!ifst.eof()) {
			if (addlist(b, ifst) != 0)
				b.count++;
		}
	}

	// Очистка контейнера от элементов
	void Clear(container &b) {
		List* current = b.Top;
		int i = 1;
		while (i < b.count)
		{
			current = current->Next;
			delete current->Priv;
			i++;
		}
		delete current;
		b.count = 0;
	}

	// Вывод содержимого контейнера в указанный поток
	void Out(container &b, ofstream &ofst)
	{
		List* current = b.Top;
		Sort(b);
		ofst << "Контейнер содержит количество элементов равное: " << b.count << endl;
		for (int j = 1; j <= b.count; j++)
		{
			ofst << j << ": ";
			Out(current->data, ofst);
			ofst << "Количество гласных в названии: " << Vowel(current->data) << endl;
			current = current->Next;
		}
	}

	void OutFilter(container &b, ofstream &ofst)
	{
		List* current = b.Top;
		ofst << "Только игровые фильмы" << endl;
		for (int i = 1; i <= b.count; i++) {
			if (current->data->key == GAME)
			{
				Out(current->data, ofst);
			}
			current = current->Next;
		}
	}

	// Мультиметод
	void MultiMethod(container& c, ofstream& ofst) {
		ofst << "Мультиметод." << endl;

		List* currentfirst;
		List* currentsecond;
		int count = 1;

		for (int i = 0; i < c.count - 1; i++)
		{
			currentfirst = c.Top;
			currentsecond = c.Top;
			currentsecond = currentsecond->Next;
			for (int k = 0; k < i; k++)
			{
				currentfirst = currentfirst->Next;
				currentsecond = currentsecond->Next;
			}
			

			for (int j = i + 1; j < c.count; j++)
			{
				switch (currentfirst->data->key)
				{
				case GAME:
				{
					switch (currentsecond->data->key)
					{
					case GAME:
					{
						ofst << "Игровой и игровой." << endl;
					}break;
					case CARTOON:
					{
						ofst << "Игровой и мультфильм." << endl;
					}break;
					case DOC:
					{
						ofst << "Игровой и документальный." << endl;
					}break;
					default:
					{
						ofst << "Неизвестный вид." << endl;
					}
					}
				}break;

				case CARTOON:
				{
					switch (currentsecond->data->key)
					{
					case GAME:
					{
						ofst << "Мультфильм и игровой." << endl;
					}break;
					case CARTOON:
					{
						ofst << "Мультфильм и мультфильм." << endl;
					}break;
					case DOC:
					{
						ofst << "Мультфильм и документальный." << endl;
					}break;
					default:
					{
						ofst << "Неизвестный вид." << endl;
					}
					}
				}break;

				case DOC:
				{
					switch (currentsecond->data->key)
					{
					case GAME:
					{
						ofst << "Документальный и игровой." << endl;
					}break;
					case CARTOON:
					{
						ofst << "Документальный и мультфильм." << endl;
					}break;
					case DOC:
					{
						ofst << "Документальный и документальный." << endl;
					}break;
					default:
					{
						ofst << "Неизвестный вид." << endl;
					}
					}
				}break;
				default:
				{
					ofst << "Неизвестный вид." << endl;
				}
				}
				ofst << count << ": ";
				Out(currentfirst->data, ofst);
				Out(currentsecond->data, ofst);
				currentsecond = currentsecond->Next;
				count++;
			}

			currentfirst = currentfirst->Next;
		}
	}
}

