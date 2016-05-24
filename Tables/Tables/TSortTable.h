#ifndef _T_SORT_TABLE_H_
#define _T_SORT_TABLE_H_

#include "TArrayTable.h"
#include "TScanTable.h"

namespace Tables
{
	/*using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;*/

	class TSortTable :public TArrayTable
	{
	private:
		void SortInsert();
		void SortHoar(int start, int end, TKey mid);

	public:
		TSortTable(int size=0) :TArrayTable(size) {};
		TSortTable(TScanTable &sc_tab);
		virtual ~TSortTable() {};

		virtual bool Find(TKey key);
		virtual void InsRec(TRecord rec);
		virtual void DelRec(TKey key);

	};

	bool TSortTable::Find(TKey key)
	{
		bool flag = false;
		int pos, left = 0, right = DataCount - 1;
		while (left <= right)
		{
			Eff++;
			pos = (right + left) / 2;
			if (pRec[pos].GetKey() == key)
			{
				right = pos;
				left = pos + 1;
				flag = true;
			}
			if (pRec[pos].GetKey() < key)
				left = pos + 1;
			else
				right = pos - 1;
		}
		if (right < 0 || pRec[pos].GetKey() != key)
			right++;
		curr = right;
		return flag;
	}

	void TSortTable::InsRec(TRecord rec)
	{
		if (IsFull()) return;
		if (!Find(rec.GetKey()))
		{
			for (int pos = DataCount; pos > curr; pos--)
			{
				pRec[pos] = pRec[pos - 1];
				Eff++;
			}
			pRec[curr] = rec;
			DataCount++;
		}
		else
		{
			//действие, если вставляемая запись уже есть в таблице
		}
	}

	void TSortTable::DelRec(TKey key)
	{
		if (IsEmpty()) return;
		if (Find(key))
		{
			for (int pos = curr; pos < DataCount - 1; pos++)
			{
				pRec[pos] = pRec[pos + 1];
				Eff++;
			}
			DataCount--;
		}
		else
		{
			//действие, если удаляемой записи в таблице нет
		}
	}

	void TSortTable::SortInsert()
	{
		TRecord _curr;
		for (int i = 1; i < DataCount; i++)
		{
			_curr = pRec[i];
			for (int j = 0; j < i; j++)
			{
				if (pRec[i] > _curr)
				{
					for (int k = i; k > j; k--)
						pRec[k] = pRec[k - 1];
					pRec[j] = _curr;
					break;
				}
			}
		}
	}

	void TSortTable::SortHoar(int start, int end, TKey mid)
	{
		int st = start, en = end;
		while (st < en)
		{
			if (pRec[st].GetKey() < mid)
				st++;
			else if (pRec[en].GetKey() > mid)
				en--;
			else
			{
				TKey tmp = pRec[st].GetKey();
				pRec[st].SetKey(pRec[en].GetKey());
				pRec[en].SetKey(tmp);
			}
		}
		TKey mid1 = pRec[(st + start) / 2].GetKey();  
		TKey mid2 = pRec[(en + end) / 2].GetKey();    
		if (st - start>1)
			SortHoar(start, st, mid1);
		if (end - en > 1)
			SortHoar(en, end, mid2);
	}

	TSortTable::TSortTable(TScanTable &sc_tab): TArrayTable(sc_tab.GetMaxSize())
	{
		int i = 0;
		for (sc_tab.Reset(); !sc_tab.IsEnd(); sc_tab.GoNext())
		{
			pRec[i] = sc_tab.GetCurr();
			i++;
			DataCount++;
		}
		SortHoar(0, DataCount-1,pRec[DataCount/2].GetKey());
	}
}

#endif