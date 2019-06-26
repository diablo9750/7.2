#ifndef _struct
#define _struct

//Содержит описание фильмов
namespace types {

	enum type { GAME = 1, CARTOON = 2, DOC = 3 };
	//Игровой
	struct game {
		type key; //ключ
		char country[100];//Страна
		char name[100];//Название фильма
		char director[100];//Имя режиссёра
	};

	//Мультфильм
	struct cartoon {
		type key; //ключ
		char country[100];//Страна
		char name[100];//Название фильма
		int type;
	};

	//Документальный
	struct doc {
		type key; //ключ
		char country[100];//Страна
		char name[100];//Название фильма
		int date;//Год выпуска
	};

	//Обобщённая структура
	struct film {
		type key; //ключ
	};

	struct List {
		List() {
			this->Next = nullptr;
			this->Priv = nullptr;
			this->data = nullptr;
		};
		List* Next;
		List* Priv;
		film* data;
	};

	// Простейший контейнер на основе одномерного массива
	struct container
	{
		List* Top;
		int count;
		void addlist();
	};
}
#endif
