#ifndef _T_TREE_TABLE_H_
#define _T_TREE_TABLE_H_

#include "TTable.h"
#include "TTreeNode.h"
#include "T_Stack.h"

namespace Tables
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	class TTreeTable :public TTable
	{
	protected:
		TTreeNode *pRoot, *pCurr;
		T_Stack <TTreeNode*> st;
		TTreeNode **pRef;
	public:
		TTreeTable() :TTable(), st(100)
		{
			pRoot = NULL;
			pCurr = NULL;
			pRef = NULL;
		}
		virtual ~TTreeTable() {};

		virtual bool Find(TKey key);
		virtual void InsRec(TRecord rec);
		virtual void DelRec(TKey key);

		virtual void Reset();
		virtual void GoNext();
		virtual bool IsEnd();
		virtual TRecord GetCurr() { return pCurr->rec; };

	};

	bool TTreeTable::Find(TKey key)
	{
		pCurr = pRoot;
		pRef = &pRoot;
		while (pCurr != NULL)
		{
			Eff++;
			if (pCurr->rec.GetKey() == key)
				return true;
			if (pCurr->rec.GetKey() < key)
				pRef = &(pCurr->pRight);
			else
				pRef = &(pCurr->pLeft);
			pCurr = *pRef;
		}
		return false;
	}

	void TTreeTable::InsRec(TRecord rec)
	{
		if (!Find(rec.GetKey()))
		{
			TTreeNode *tmp = new TTreeNode(rec);
			*pRef = tmp;
			DataCount++;
		}
	}
}


#endif