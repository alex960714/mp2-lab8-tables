// Tables_console.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "TRecord.h"
#include "TScanTable.h"
#include "TSortTable.h"
#include "THashTable.h"
#include "TTreeTable.h"
#include <string.h>
#include <iostream>
using namespace std;


int main()
{
	const int size = 5;
	Tables::TScanTable scan(size);
	Tables::TSortTable sort(size);
	Tables::THashTable hash(size+2,2);
	Tables::TTreeTable tree;
	TRecord rec;
	TKey key;
	TValue val;
	setlocale(LC_CTYPE, "Russian");
	cout << "Заполните таблицу:" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> rec;
		TRecord rec2(rec);
		scan.InsRec(rec);
		sort.InsRec(rec);
		hash.InsRec(rec);
		tree.InsRec(rec);
	}
	cout << "Таблица для просмотра:" << endl ;
	scan.Print();
	cout << "Отсортированная таблица:" << endl;
	sort.Print();
	cout << "Хэш-таблица:" << endl;
	hash.Print();
	cout << "Древовидная таблица:" << endl;
	tree.Print();
    return 0;
}

