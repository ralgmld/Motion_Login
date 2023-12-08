#pragma once
#include "afxdialogex.h"


// LOGINHOMEDlg 대화 상자

class LOGINHOMEDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LOGINHOMEDlg)

public:
	LOGINHOMEDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LOGINHOMEDlg();
	CBrush m_brush1;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGINHOME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		BOOL OnInitDialog();
	BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBitmapButton MotionChangeBtn;
	CBitmapButton WebBtn;
	CString m_name;
	CString m_birth;
	afx_msg void OnBnClickedWeb();
	afx_msg void OnBnClickedMotionch();
	afx_msg void OnBnClickedMotiondel();
};
