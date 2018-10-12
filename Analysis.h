#pragma once
#include <afxtempl.h>
typedef CMap< int, int, CString, CString> MAP;
class CAnalysis
{
public:
	CAnalysis();
	~CAnalysis();
	void Scan();
	int Valueable(CString str, int i);
	void InitList(CString str);
	CString Convert();

private:
	bool IsNum(CString str);
	int IsExp(CString str, int i);//这句用来判断是否为注释
	int IsKey(CString str);
	CList<CString, CString&> list;//保存写入的程序
	bool IsChar(CString str, int i);
	bool IsAble(CString str, int i);
private:
	void Add(int key, CString value);
	void Clear();
	CList<int, int> Keys;
	CList<CString, CString&> Values;
	int position = 0;
};

