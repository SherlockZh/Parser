
// LexicalAnalyDlg.h : ͷ�ļ�
//

#pragma once


// CLexicalAnalyDlg �Ի���
class CLexicalAnalyDlg : public CDialogEx
{
// ����
public:
	CLexicalAnalyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LEXICALANALY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
