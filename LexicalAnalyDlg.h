
// LexicalAnalyDlg.h : 头文件
//

#pragma once


// CLexicalAnalyDlg 对话框
class CLexicalAnalyDlg : public CDialogEx
{
// 构造
public:
	CLexicalAnalyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LEXICALANALY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_String;
	afx_msg void OnBnClickedButton2();
	CString m_Result;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
};
