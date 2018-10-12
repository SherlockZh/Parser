
// LexicalAnalyDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLexicalAnalyDlg �Ի���



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


// CLexicalAnalyDlg ��Ϣ�������

BOOL CLexicalAnalyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLexicalAnalyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
//���ļ�
void CLexicalAnalyDlg::OnBnClickedButton2()
{
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, 4 | 2,
		_TEXT("�ı��ļ�(*.txt,*.ini,*.log)|*.txt;*.ini;*.log|ȫ���ļ�(*.*)|*.*||"));
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_Result = "";
	m_String = "";
	UpdateData(FALSE);
}


void CLexicalAnalyDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fDlg(FALSE, _TEXT("txt"),NULL, 4 | 2,
		_TEXT("�ı��ļ�(*.txt,*.ini,*.log)|*.txt;*.ini;*.log|ȫ���ļ�(*.*)|*.*||"));
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
