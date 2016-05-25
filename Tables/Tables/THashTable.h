#ifndef _T_HASH_TABLE_H_
#define _T_HASH_TABLE_H_

#include "TTable.h"

namespace Tables
{
	/*using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;*/

	class THashTable :public TTable
	{
	protected:
		int HashFunc(TKey key);

		int maxSize, curr, step, free;
		TRecord *pRec;

	public:
		THashTable(int _size=0, int _step=0);
		virtual ~THashTable() { delete[] pRec; pRec = NULL; };

		virtual bool IsFull() { return maxSize == DataCount; };
		virtual bool Find(TKey key);
		virtual void InsRec(TRecord rec);
		virtual void DelRec(TKey key);

		virtual void Reset();
		virtual void GoNext();
		virtual bool IsEnd() { return curr == maxSize; };
		virtual TRecord GetCurr() { return pRec[curr]; };
	};

	int THashTable::HashFunc(TKey key)
	{
		int k = 1, R = 0;
		for (int i = 0; i < key.length(); i++)
		{
			R += key[i] * k;
			k *= 2;
		}
		return R;
	}

	THashTable::THashTable(int _size, int _step)
	{
		maxSize = _size;
		step = _step;
		pRec = new TRecord[maxSize];
		for (int i = 0; i < maxSize; i++)
		{
			pRec[i].SetKey("");
			pRec[i].SetValue("");
		}
		curr = -1;
		DataCount = 0;
		Eff = 0;
	}

	bool THashTable::Find(TKey key)
	{
		curr = HashFunc(key) % maxSize;
		free = -1;
		for (int i = 0; i < maxSize; i++)
		{
			Eff++;
			if (pRec[curr].GetKey() == key)
				return true;
			if (pRec[curr].GetKey() == "&" && free == -1)
				free = curr;
			if (pRec[curr].GetKey() != "")
			{
				curr = (step + curr) % maxSize;
			}
			else break;
		}
		if (free != -1)
			curr = free;
		return false;
	}

	void THashTable::InsRec(TRecord rec)
	{
		if (IsFull()) return;
		if (!Find(rec.GetKey()))
		{
			pRec[curr] = rec;
			DataCount++;
		}
		else
		{
			cout << "Данная запись уже есть в таблице" << endl;
		}
	}

	void THashTable::DelRec(TKey key)
	{
		if (IsEmpty()) return;
		if (Find(key))
		{
			pRec[curr].SetKey("&");
			DataCount--;
		}
		else
		{
			cout << "Данной записи нет в таблице" << endl;
		}
	}

	void THashTable::Reset()
	{
		curr = 0;
		while (curr < maxSize && (pRec[curr].GetKey() == "&" || pRec[curr].GetKey() == ""))
			curr++;
	}

	void THashTable::GoNext()
	{
		curr++;
		while (curr<maxSize && (pRec[curr].GetKey() == "&" || pRec[curr].GetKey() == ""))
			curr++;
	}
}


#endif
