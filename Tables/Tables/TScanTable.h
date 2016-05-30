#ifndef _T_SCAN_TABLE_H_
#define _T_SCAN_TABLE_H_

#include "TArrayTable.h"

namespace Tables
{
/*	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;*/

	class TScanTable :public TArrayTable
	{
	public:
		TScanTable(int size=0) :TArrayTable(size) {};
		virtual ~TScanTable() {};

		virtual bool Find(TKey key);
		virtual void InsRec(TRecord rec);
		virtual void DelRec(TKey key);
	};



	bool TScanTable::Find(TKey key)
	{
		for (Reset(); !IsEnd(); GoNext())
		{
			Eff++;
			if (pRec[curr].GetKey() == key)
				return true;
		}
		return false;
	}

	void TScanTable::InsRec(TRecord rec)
	{
		if (IsFull()) return;
		if (!Find(rec.GetKey()))
		{
			pRec[curr] = rec;
			DataCount++;
			Eff++;  //???
		}
		else
		{
			cout << "Данная запись уже есть в таблице" << endl;
		}
	}

	void TScanTable::DelRec(TKey key)
	{
		if (IsEmpty()) return;
		if (Find(key))
		{
			pRec[curr] = pRec[DataCount - 1];
			DataCount--;
			Eff++;
		}
		else
		{
			cout << "Данной записи нет в таблице" << endl;
		}
	}

}


#endif
