#pragma once
#include "afxdialogex.h"


// LOGINDlg 대화 상자

class LOGINDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LOGINDlg)

public:
	LOGINDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	CBrush m_brush1;
	virtual ~LOGINDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	HICON m_loginico;
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedJoinbtn();
	CBitmapButton LoginMotionBtn;
	afx_msg void OnBnClickedLoginmotion();
	CString LOGIN_NAME;
	CString LOGIN_BIRTH;
	char* name;
	char* birth;
};
