
// LexicalAnalyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LexicalAnaly.h"
#include "LexicalAnalyDlg.h"
#include "afxdialogex.h"
#include "Analysis.h"
#include <string>
#include <fstream>
#include "LexAnalysis.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLexicalAnalyDlg 对话框



CLexicalAnalyDlg::CLexicalAnalyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLexicalAnalyDlg::IDD, pParent)
	, m_String(_T(""))
	, m_Result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLexicalAnalyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_String);
	DDX_Text(pDX, IDC_EDIT2, m_Result);
}

BEGIN_MESSAGE_MAP(CLexicalAnalyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLexicalAnalyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLexicalAnalyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLexicalAnalyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CLexicalAnalyDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CLexicalAnalyDlg 消息处理程序

BOOL CLexicalAnalyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLexicalAnalyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLexicalAnalyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLexicalAnalyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLexicalAnalyDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	m_Result = "";
	initKeyMapping();
	initOperMapping();
	initLimitMapping();
	initNode();
	scanner();
	printNodeLink();

	ifstream readFile;
	readFile.open("output.txt");
	string code;
	while (getline(readFile, code))
	{
		m_Result += code.c_str();
		m_Result += "\r\n";
	}
	UpdateData(FALSE);
}
//打开文件
void CLexicalAnalyDlg::OnBnClickedButton2()
{
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, 4 | 2,
		_TEXT("文本文件(*.txt,*.ini,*.log)|*.txt;*.ini;*.log|全部文件(*.*)|*.*||"));
	if (fDlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_PATH, fDlg.GetPathName());
		CFile fFile(fDlg.GetPathName(), CFile::modeRead);
		CStringA strFile;
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());
		fFile.Close();
		strFile.ReleaseBuffer();
		m_String = CString(strFile);
	}
	UpdateData(FALSE);
}
void CLexicalAnalyDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Result = "";
	m_String = "";
	UpdateData(FALSE);
}


void CLexicalAnalyDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fDlg(FALSE, _TEXT("txt"),NULL, 4 | 2,
		_TEXT("文本文件(*.txt,*.ini,*.log)|*.txt;*.ini;*.log|全部文件(*.*)|*.*||"));
	if (fDlg.DoModal() == IDOK)
	{
		CFile fFile(fDlg.GetPathName(),CFile::modeCreate|CFile::modeWrite);
		CStringA strFile;
		strFile = m_Result;
		fFile.Write(strFile, strFile.GetLength());
		fFile.Close();
		strFile.ReleaseBuffer();
		//m_String = CString(strFile);
	}
	UpdateData(FALSE);
}
