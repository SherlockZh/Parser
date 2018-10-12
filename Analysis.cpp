#include "stdafx.h"
#include "Analysis.h"
#include <afxtempl.h>
/* 单词种别码*/
#define _CHAR 1
#define _INT  2
#define _SHORT 3
#define _LONG 4
#define _SIGNED 5
#define _UNSIGNED 6
#define _FLOAT 7
#define _DOUBLE 8
#define _CONST 9
#define _VOID 10
#define _VOLATILE 11
#define _ENUM 12
#define _STRUCT 13
#define _UNION 14
#define _TYPEDEF 15
#define _AUTO 16
#define _EXTERN 17
#define _STATIC 18
#define _REGISTER 19
#define _IF 20
#define _ELSE 21
#define _SWITCH 22
#define _CASE 23
#define _DEFAULT 24
#define _WHILE 25
#define _DO 26
#define _FOR 27
#define _BREAK 28
#define _CONTINUE 29
#define _GOTO 30
#define _RETURN 31
#define _SIZEOF 32
#define _INCLUDE 33
#define _DEFINE 34
/* 以上为关键字的种别码*/
#define _ID 40    //标识符 
#define _NUM 50    //数 
#define _AS 51    //= 
#define _PLUS 52    //+ 
#define _SUB 53    //- 
#define _TIMES 54    // * 
#define _DIV 55    // / 
#define _LP 56    // (
#define _RP 57    // )
#define _LB1 58    // [
#define _RB1 59    // ]
#define _LB2 60    // {
#define _RB2 61    // }
#define _COM 62    // ,
#define _COL 63    // :
#define _SEM 64    // ;
#define _POINT 65    // .
#define _LG 66    // >
#define _LT 67    // <
#define _ME 68    // >=
#define _LE 69    // <=
#define _EQ 70    // ==
#define _NE 71    // !=
#define _A 72    // >>
#define _B 73    // >>=
#define _C 74    // <<
#define _D 75    // <<=
#define _E 76    // &
#define _F 76    // &&
#define _G 77    // &=
#define _H 78   // |
#define _I 79   // ||
#define _J 80  // |=
#define _K 81  // ~
#define _L 82  // ++
#define _M 83  //  --
#define _N 84  // ->
#define _O 85  // +=
#define _P 86  // -=
#define _Q 87  // *=
#define _R 88  // /=
#define _S 89  // %=
#define _TT 90  // ^=
#define _U 91  //  %
#define _V 92  //  "
#define _W 93  //  '
#define _X 94  //  ?
#define _EROOR -1      // 错误 
int ERROR_NUM = 0;    //记载词法编译错误个数 
CAnalysis::CAnalysis()
{
}
CAnalysis::~CAnalysis()
{
}

bool CAnalysis::IsNum(CString str)
{
	int y;
	int i;
	int j = 0;
	int k = 0;
	for (i = 0; i<str.GetLength(); i++)
	{
		if (!(str[i] <= '9'&&str[i] >= '0'))
		{
			k++;
			if ((k - j)>1){
				//cout << "数字串" << str << "出现词法错误！" << endl;
				return false;
			}
			if (str[i] == '.')
			{
				j++;
				if (j > 1)
				{
					//cout << "数字串" << str << "出现词法错误！" << endl;
					return false;
				}
			}
			else if ((str[i] == 'E' || str[i] == 'e') && (str[i - 1] <= '9'&&str[i - 1] >= '0') && ((str[i + 1] <= '9'&&str[i + 1] >= '0') || (y = i + 1) == str.GetLength()))
				continue;
			else{
				//cout << "数字串" << str << "出现词法错误！" << endl;
				return false;
			}

		}
	}
	return true;
}

int CAnalysis::Valueable(CString str, int i)
{
	while (true)
	{
		if (str[i] != ' '&&str[i] != '\n'&&str[i]!='\r')
			return i;
		i++;
	}
	return 0;
}
int CAnalysis::IsExp(CString str, int i)
{
	if (str[i] == '/'&&str[i + 1] == '/')
	{
		while (str[i] != '\n'){
			i++;
		}
	}

	return i;
}
int CAnalysis::IsKey(CString str)
{
	CString p[34] = { L"char", L"int", L"short", L"long", L"signed", L"unsigned", L"float", L"double", L"const", L"void", 
		L"volatile", L"enum", L"struct", L"union", L"typedef", L"auto", L"extern", 
		L"static", L"register", L"if", L"else", L"switch", L"case", L"default", 
		L"while", L"do", L"for", L"break", L"continue", L"goto", 
		L"return", L"sizeof", L"#include", L"#define" };
	CList<CString, CString&> ppp; //(p, p + 34);
	for (int i = 0; i < 34; i++)
	{
		ppp.AddHead(p[i]);
	}
	int u; 
	for (u = 0; u < 34; u++)
	{
		if (str==p[u])
			return (u + 1);
	}
	return 0;
}


void CAnalysis::Scan()
{
	Clear();
	POSITION pos = list.GetHeadPosition();
	for (int i = 0; i < list.GetCount(); i++)
	{
		//if (list.)
		pos = list.FindIndex(i);
		if (list.GetAt(pos).GetLength() == 1)
		{
			//串长为1
			if (list.GetAt(pos) == ">")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					//Add(_ME, jk);
					Add(_ME, jk);
					continue;
				}
				else if (list.GetAt(pos) == ">"&&list.GetAt(list.FindIndex(i + 2)) != "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					//Add(_A, jk);
					Add(_A, jk);
					continue;
				}
				else if (list.GetAt(pos) == ">"&&list.GetAt(list.FindIndex(i + 2)) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					jk += list.GetAt(list.FindIndex(i + 2));
					i++;
					Add(_B, jk);
					continue;
				}
				else
				{
					Add(_LG, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "<")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_LE, jk);
					continue;
				}
				else if (list.GetAt(pos) == "<"&&list.GetAt(list.FindIndex(i + 2)) != "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_C, jk);
					continue;
				}
				else if (list.GetAt(pos) == ">"&&list.GetAt(list.FindIndex(i + 2)) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					jk += list.GetAt(list.FindIndex(i + 2));
					i++;
					Add(_D, jk);
					continue;
				}
				else
				{
					Add(_LT, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "!")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_NE, jk);
					continue;
				}
				else
				{
					Add(_LT, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos)=="=")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_EQ, jk);
					continue;
				}
				else
				{
					Add(_AS, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "&")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "&")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_F, jk);
					continue;
				}
				else if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_G, jk);
					continue;
				}
				else
				{
					Add(_E, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "|")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "|")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_I, jk);
					continue;
				}
				else if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_J, jk);
					continue;
				}
				else
				{
					Add(_H, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "(")
			{
				Add(_LP, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == ")")
			{
				Add(_RP, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == "[")
			{
				Add(_LB1, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == "]")
			{
				Add(_RB1, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == "~")
			{
				Add(_K, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == ",")
			{
				Add(_COM, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == "{")
			{
				Add(_LB2, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == ":")
			{
				Add(_COL, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == ";")
			{
				Add(_SEM, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == "}")
			{
				Add(_RB2, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == "*")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_Q, jk);
					continue;
				}
				else
				{
					Add(_TIMES, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "/")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_R, jk);
					continue;
				}
				if (list.GetAt(pos) == "/")
				{
					i = i + 2;
					//读到行尾
					while (i<list.GetCount()&&list.GetAt(list.FindIndex(i))!="/")
					{
						i++;
					}
					continue;
				}
				else if (list.GetAt(pos) == "*")
				{
					i = i + 2;
					while (i < list.GetCount() && (list.GetAt(list.FindIndex(i-1)) != "*" || list.GetAt(list.FindIndex(i)) != "/"))
						i++;
					continue;
				}
				else
				{
					Add(_DIV, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "%")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_S, jk);
					continue;
				}
				else
				{
					Add(_U, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos).GetAt(0) == '"')
			{
				Add(_V, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos).GetAt(0) == '\'')
			{
				Add(_W, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos).GetAt(0) == '?')
			{
				Add(_X, list.GetAt(list.FindIndex(i)));
			}
			else if (list.GetAt(pos) == "+")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_O, jk);
					continue;
				}
				else if (list.GetAt(pos)=="+")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_L, jk);
					continue;
				}
				else if ((list.GetAt(list.FindIndex(i - 1)) == "=" || list.GetAt(list.FindIndex(i - 1)) == "(") && IsNum(list.GetAt(list.FindIndex(i + 1))))
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_NUM, jk);
					continue;
				}
				else
				{
					Add(_PLUS, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos) == "-")
			{
				pos = list.FindIndex(i + 1);
				if (list.GetAt(pos) == "=")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_P, jk);
					continue;
				}
				else if (list.GetAt(pos) == "-")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_M, jk);
					continue;
				}
				else if (list.GetAt(pos) == ">")
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_N, jk);
					continue;
				}
				else if ((list.GetAt(list.FindIndex(i - 1)) == "=" || list.GetAt(list.FindIndex(i - 1)) == "(") && IsNum(list.GetAt(list.FindIndex(i + 1))))
				{
					CString jk = list.GetAt(list.FindIndex(i));
					jk += list.GetAt(pos);
					i++;
					Add(_NUM, jk);
					continue;
				}
				else
				{
					Add(_SUB, list.GetAt(list.FindIndex(i)));
				}
			}
			else if (list.GetAt(pos).GetAt(0) <= '9'&&list.GetAt(pos).GetAt(0) >= '0')
			{
				Add(_NUM, list.GetAt(list.FindIndex(i)));
			}
			else
			{
				Add(_ID, list.GetAt(list.FindIndex(i)));
			}

		}
		else if ((list.GetAt(pos).GetAt(0)<='9'&&list.GetAt(pos).GetAt(0)>='0')||list.GetAt(pos).GetAt(0)=='.')
		{
			if (!IsNum(list.GetAt(pos)))ERROR_NUM++;
			/*else if ((list.GetAt(list.FindIndex(i + 1)).GetAt(0) == '+' || list.GetAt(list.FindIndex(i + 1)).GetAt(0) == '-') && IsNum(list.GetAt(list.FindIndex(i + 2))))
			{
				CString jk = list.GetAt(list.FindIndex(i));
				jk += list.GetAt(list.FindIndex(i++));
				jk += list.GetAt(list.FindIndex(i++));
				Add(_NUM, jk);
				continue;
			}*/
			else
				Add(_NUM, list.GetAt(list.FindIndex(i)));
		}
		else if (IsKey(list.GetAt(pos)))
		{
			Add(IsKey(list.GetAt(list.FindIndex(i))), list.GetAt(list.FindIndex(i)));
		}
		else
		{
			Add(_ID, list.GetAt(list.FindIndex(i)));
		}
	}
	//return map;
}
void CAnalysis::Add(int key, CString value)
{
	Keys.AddTail(key);
	Values.AddTail(value);
	++position;
}
void CAnalysis::Clear()
{
	Keys.RemoveAll();
	Values.RemoveAll();
	position = 0;
}
void CAnalysis::InitList(CString str)
{
	list.RemoveAll();
	for (int i = 0; i < str.GetLength();i++)
	{
		if (i>0&&(str[i] == '/' || str[i - 1] == '/'))
		{
			while (i < str.GetLength() && str[i] != 10)
			{
				i++;
			}
		}
		if (IsAble(str,i))//如果不是空格或者换行
		{
			if (!IsChar(str, i))
			{
				list.AddTail((CString)str[i]);
				continue;
			}
			CString st;
			while(IsChar(str, i))
			{
				st += str[i];
				i++;
			}
			i--;
			list.AddTail(st);
		}
	 }
}
bool CAnalysis::IsChar(CString str,int i)
{
	if (str[i] >= '0'&&str[i] <= '9' || (str[i] >= 'a'&&str[i] <= 'z') || (str[i] >= 'A'&&str[i] <= 'Z')||str[i]=='_')
	{
		return true;
	}
	else
		return false;
}

bool CAnalysis::IsAble(CString str, int i)
{
	if (str[i] != 32&&str[i] != 13&&str[i] != 10)
		return true;
	else
		return false;
}

CString CAnalysis::Convert()
{
	CString str;
	POSITION posKey, posValue;
	posKey = Keys.GetHeadPosition();
	posValue = Values.GetHeadPosition();
	while (posKey&&posValue)
	{
		CString s;
		s.Format(L"（%d : %s）\r\n", Keys.GetNext(posKey), Keys.GetNext(posValue));
		str += s;
	}
	return str;
}
