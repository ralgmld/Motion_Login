#pragma once
#include "afxdialogex.h"


// SIGNUPDlg 대화 상자

class SIGNUPDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SIGNUPDlg)

public:
	SIGNUPDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	CBrush m_brush1;
	virtual ~SIGNUPDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	HICON m_signupico;
	
	afx_msg
		BOOL OnInitDialog();
	void OnBnClickedButton1();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEdit2();
//	afx_msg void OnNcPaint();
//	afx_msg void OnPaint();
	CBitmapButton SignupMotionBtn;
	afx_msg void OnBnClickedButton2();
};
