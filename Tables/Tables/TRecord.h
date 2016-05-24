#ifndef _T_RECORD_H_
#define _T_RECORD_H_

#include <string.h>
#include <string>
#include <iostream>
using namespace std;

typedef string TKey;
typedef string TValue;

class TRecord
{
private:
	TKey key;
	TValue val;

public:
	TRecord(TKey _k = "", TValue _v = "") { key = _k; val = _v; };
	~TRecord() {};

	void SetKey(TKey _k) { key = _k; };
	TKey GetKey() { return key; };
	void SetValue(TValue _v) { val = _v; };
	TValue GetValue() { return val; };

	bool operator==(const TRecord &rec) { return this->key == rec.key; };
	bool operator<(const TRecord &rec) { return this->key < rec.key; };
	bool operator>(const TRecord &rec) { return this->key > rec.key; };

	TRecord& operator=(const TRecord &rec) 
	{ 
		this->key = rec.key; 
		this->val = rec.val;
		return *this;
	}


	friend istream& operator>>(istream &is, TRecord &rec)
	{
		string _key, _val;
		is >> _key;
		is >> _val;
		rec.key = _key;
		rec.val = _val;
		return is;
	}

	friend ostream& operator<<(ostream &os, const TRecord &rec)
	{
		string _key = rec.key;
		string _val = rec.val;
		os << " " << _key << " | " << _val << " " << endl;
		return os;
	}
};

/*istream& operator>>(istream &is, TKey &key)
{
	is >> key;
	return is;
}*/

/*istream& operator>>(istream &is, TValue val)
{
	is >> val;
	return is;
}*/

/*ostream& operator<<(ostream &os, const TKey &key)
{
	os << key;
	return os;
}*/

/*ostream& operator<<(ostream &os, TValue val)
{
	os << val;
	return os;
}*/

#endif
