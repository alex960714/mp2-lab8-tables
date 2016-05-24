// Tables_console.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	cout << "��������� �������:" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> rec;
		TRecord rec2(rec);
		scan.InsRec(rec);
		sort.InsRec(rec);
		hash.InsRec(rec);
		tree.InsRec(rec);
	}
	cout << "������� ��� ���������:" << endl ;
	scan.Print();
	cout << "��������������� �������:" << endl;
	sort.Print();
	cout << "���-�������:" << endl;
	hash.Print();
	cout << "����������� �������:" << endl;
	tree.Print();
    return 0;
}

