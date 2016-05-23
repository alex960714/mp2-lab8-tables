#ifndef _T_ARRAY_TABLE_H_
#define _T_ARRAY_TABLE_H_

#include "TTable.h"

namespace Tables
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	class TArrayTable :public TTable
	{
	protected:
		TRecord *pRec;
		int curr, maxSize;

	public:
		TArrayTable(int size);
		virtual ~TArrayTable() {};

		virtual bool IsFull() { return maxSize == DataCount; };
		virtual TRecord GetCurr() { return pRec[curr]; };
		virtual void Reset() { curr = 0; }
		virtual void GoNext() { curr++; }
		virtual bool IsEnd() { return curr == DataCount; };

		int GetMaxSize() const { return maxSize; };
	};

	TArrayTable::TArrayTable(int size)
	{
		maxSize = size;
		pRec = new TRecord[maxSize];
		curr = -1;
		DataCount = 0;
		Eff = 0;
	}

}


#endif
