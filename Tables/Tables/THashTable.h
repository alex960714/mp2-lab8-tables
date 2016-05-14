#ifndef _T_HASH_TABLE_H_
#define _T_HASH_TABLE_H_

#include "TTable.h"

namespace Tables
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	class THashTable :public TTable
	{
	protected:
		int HashFunc(TKey key);

		int maxSize, curr, step, free;
		TRecord *pRec;

	public:
		THashTable(int _size, int _step);
		virtual ~THashTable() { delete[] pRec; pRec = NULL; };

		virtual bool IsFull() { return maxSize == DataCount; };
		virtual bool Find(TKey key);
		virtual void InsRec(TRecord rec);
		virtual void DelRec(TKey key);

		virtual void Reset();
		virtual void GoNext();
		virtual bool IsEnd();
		virtual TRecord GetCurr();
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
		curr = -1;
		DataCount = 0;
		Eff = 0;
	}
}


#endif
