#ifndef _T_TREE_TABLE_H_
#define _T_TREE_TABLE_H_

#include "TTable.h"
#include "TTreeNode.h"
#include "T_Stack.h"

namespace Tables
{
	/*using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;*/

	class TTreeTable :public TTable
	{
	protected:
		TTreeNode *pRoot, *pCurr;
		T_Stack <TTreeNode*> st;
		TTreeNode **pRef;
		int pos;

	public:
		TTreeTable() :TTable(), st(100)
		{
			pRoot = NULL;
			pCurr = NULL;
			pRef = NULL;
		}
		virtual ~TTreeTable() {};

		virtual bool IsFull() { return false; };
		virtual bool Find(TKey key);
		virtual void InsRec(TRecord rec);
		virtual void DelRec(TKey key);

		virtual void Reset();
		virtual void GoNext();
		virtual bool IsEnd() { return pos == DataCount; };
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
		else
		{
			cout << "Данная запись уже есть в таблице" << endl;
		}
	}

	void TTreeTable::DelRec(TKey key)
	{
		if (!Find(key))
		{
			cout << "Данной записи нет в таблице" << endl;
			return;
		}
		TTreeNode *p = *pRef;
		if ((*pRef)->pLeft != NULL || (*pRef)->pRight != NULL)
		{
			if ((*pRef)->pLeft == NULL)
				*pRef = (*pRef)->pRight;
			else if ((*pRef)->pRight == NULL)
				*pRef = (*pRef)->pLeft;
			else
			{
				TTreeNode **tmp = &((*pRef)->pLeft);
				(*pRef)->rec = (*tmp)->rec;
				p = *tmp;
				while ((*tmp)->pRight != NULL)
				{
					tmp = &((*tmp)->pRight);
					Eff++;
					(*pRef)->rec = (*tmp)->rec;
					p = *tmp;
				}
				*tmp = (*tmp)->pLeft;
			}
		}
		else 
			*pRef = NULL;
		delete p;
		DataCount--;
	}

	void TTreeTable::Reset()
	{
		pCurr = pRoot;
		st.Clear();
		pos = 0;
		while (pCurr != NULL)
		{
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
		pCurr = st.Pop();
	}

	void TTreeTable::GoNext()
	{
		if (pCurr != NULL)
		{
			pos++;
			pCurr = pCurr->pRight;
			while (pCurr != NULL)
			{
				st.Push(pCurr);
				pCurr = pCurr->pLeft;
			}
			if (!st.IsEmpty())
				pCurr = st.Pop();
		}
	}

}


#endif