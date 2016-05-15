#ifndef _T_TABLE_H_
#define _T_TABLE_H_

#include "TRecord.h"

namespace Tables
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	class TTable
	{
	protected:
		int DataCount, Eff;

	public:
		TTable() { DataCount = 0; Eff = 0; };
		virtual ~TTable() {};

		int GetDataCount() const { return DataCount; };
		int GetEff() const { return Eff; };
		void ResetEff() { Eff = 0; };

		bool IsEmpty() { return DataCount == 0; };
		virtual bool IsFull() = 0;

		virtual bool Find(TKey key) = 0;
		virtual void DelRec(TKey key) = 0;
		virtual void InsRec(TRecord rec) = 0;

		virtual void Reset() = 0;
		virtual void GoNext() = 0;
		virtual bool IsEnd() = 0;

		virtual TRecord GetCurr() = 0;
		void Print(DataGridView^ grid);
	};

	void TTable::Print(DataGridView^ grid)
	{
		grid->ColumnCount = 2;
		grid->RowCount = DataCount;

		int i = 0;
		for (Reset(); !IsEnd(); GoNext())
		{
			TRecord curr = GetCurr();
			grid[0, i]->Value = gcnew System::String(curr.GetKey().c_str());
			grid[1, i]->Value = gcnew System::String(curr.GetValue().c_str());
		}
	}

}

#endif


