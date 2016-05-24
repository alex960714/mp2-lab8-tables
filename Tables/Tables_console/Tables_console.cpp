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
	setlocale(LC_CTYPE, "Russian");
	int maxSize, step;
	cout << "������� ������������ ������ ������:" << endl;
	cin >> maxSize;
	cout << "������� �������� ���� ��� ���-�������:" << endl;
	cin >> step;
	Tables::TScanTable *scan = new Tables::TScanTable(maxSize);
	Tables::TSortTable *sort = new Tables::TSortTable(maxSize);
	Tables::THashTable *hash= new Tables::THashTable(maxSize,step);
	Tables::TTreeTable *tree=new Tables::TTreeTable;
	Tables::TTable *tab = scan;
	TRecord rec;
	TKey key;
	TValue val;
	int op = 1;
	int tab_num = 1;
	int size;

	do
	{
		switch (op)
		{
		case 1: scan = new Tables::TScanTable(maxSize);
			sort = new Tables::TSortTable(maxSize);
			hash = new Tables::THashTable(maxSize, step);
			tree = new Tables::TTreeTable;
			tab = scan;
			cout << "������� ����� ��������� � �������:" << endl;
			cin >> size;
			cout << "��������� �������:" << endl;
			for (int i = 0; i < size; i++)
			{
				cin >> rec;
				scan->InsRec(rec);
				sort->InsRec(rec);
				hash->InsRec(rec);
				tree->InsRec(rec);
			}
			break;

		case 2: cout << "�������� ��� �������" << endl;
			cout << "1. ������� ��� ���������" << endl;
			cout << "2. ��������������� �������" << endl;
			cout << "3. ���-�������" << endl;
			cout << "4. ����������� �������" << endl;
			cin >> tab_num;
			switch (tab_num)
			{
			case 1: tab = scan;
				break;
			case 2: tab = sort;
				break;
			case 3: tab = hash;
				break;
			case 4: tab = tree;
				break;
			default: cout << "������������ ����!" << endl;
			}
			break;

		case 3: switch (tab_num)
		{
		case 1: cout << "������� ��� ���������:" << endl;
			scan->Print();
			break;

		case 2: cout << "��������������� �������:" << endl;
			sort->Print();
			break;

		case 3: cout << "���-�������:" << endl;
			hash->Print();
			break;

		case 4: cout << "����������� �������:" << endl;
			tree->Print();
			break;
		}
			break;

		case 4: cout << "������� ���� �������� ������:" << endl;
				cin >> key;
				tab->ResetEff();
				if (tab->Find(key))
					cout << "������� ������ - " << tab->GetCurr() << endl;
				else
					cout << "������� �� ������" << endl;
				cout << "������������� - " << tab->GetEff() << endl;
				break;

		case 5: cout << "��������� ���� ��������, ������� ������ ��������:" << endl;
			cin >> rec;
			tab->ResetEff();
			tab->InsRec(rec);
			cout << "������������� - " << tab->GetEff() << endl;
			break;

		case 6: cout << "������� ���� ��������, ������� ������ �������:" << endl;
			cin >> key;
			tab->ResetEff();
			tab->DelRec(key);
			cout << "������������� - " << tab->GetEff() << endl;
			break;

		case 7: sort = new Tables::TSortTable(*scan);
			tab_num = 2;
			cout << "������� �������������" << endl;
			break;

		case 8: break;

		default: cout << "������������ ����! ������� �������� ������" << endl;
		}
		cout << "�������� ��������:" << endl;
		cout << "1. ��������� �������" << endl;
		cout << "2. ������� ��� ������� (�� ��������� - ������� ��� ���������)" << endl;
		cout << "3. ����� ������� �� �����" << endl;
		cout << "4. ����� ��������" << endl;
		cout << "5. �������� �������" << endl;
		cout << "6. ������� �������" << endl;
		cout << "7. ������������� ������� ��� ���������" << endl;
		cout << "8. ���������� ������" << endl;
		cin >> op;
	} while (op != 8);
	
    return 0;
}

