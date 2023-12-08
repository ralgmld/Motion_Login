// SIGNUPDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Motion.h"
#include "afxdialogex.h"
#include "Motion.h"
#include "SIGNUPDlg.h"
#include "LOGINDlg.h"
#include "includePython.h"
#include "string"
#include "stdio.h"
#include "iostream"
#include "vector"
#include "atlstr.h"
#include "object.h"


// SIGNUPDlg 대화 상자

IMPLEMENT_DYNAMIC(SIGNUPDlg, CDialogEx)

SIGNUPDlg::SIGNUPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIGNUP, pParent)
{
	m_signupico = AfxGetApp()->LoadIcon(IDI_SIGNUPICON);
}

SIGNUPDlg::~SIGNUPDlg()
{
}

void SIGNUPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SignupMotion, SignupMotionBtn);
}


BEGIN_MESSAGE_MAP(SIGNUPDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &SIGNUPDlg::OnBnClickedButton1)
//	ON_WM_CTLCOLOR()
ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR()
//ON_EN_CHANGE(IDC_EDIT2, &SIGNUPDlg::OnEnChangeEdit2)
//ON_WM_NCPAINT()
//ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &SIGNUPDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// SIGNUPDlg 메시지 처리기

BOOL SIGNUPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("SIGN UP")); // 타이틀바 제목 변경
	SetBackgroundColor(RGB(0, 38, 77));

	SignupMotionBtn.LoadBitmaps(IDB_BITMAP1, NULL, NULL, NULL); // 모션 등록 버튼 이미지 입히기
	SignupMotionBtn.SizeToContent();

	m_brush1.CreateSolidBrush(RGB(0, 38, 77));

	SetIcon(m_signupico, TRUE);
	SetIcon(m_signupico, FALSE);

	return TRUE;
}

BOOL SIGNUPDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255)); // 다이얼로그 배경색 지정

	return TRUE;
}

HBRUSH SIGNUPDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(0, 38, 77));  // 아이디, 생년월일 STATIC TEXT 배경색 지정
		return m_brush1;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void SIGNUPDlg::OnBnClickedButton1()
{
	CString JOIN_NAME;
	CString JOIN_BIRTH;

	GetDlgItemText(IDC_SignupName, JOIN_NAME);
	GetDlgItemText(IDC_SignupBirth, JOIN_BIRTH);

	int name_size = JOIN_NAME.GetLength();
	name_size = (name_size * 3) + 1;
	char* name = new char[name_size];
	strcpy_s(name, name_size, CW2A(JOIN_NAME, CP_UTF8));

	int birth_size = JOIN_BIRTH.GetLength();
	birth_size = (birth_size * 3) + 1;
	char* birth = new char[birth_size];
	strcpy_s(birth, birth_size, CW2A(JOIN_BIRTH, CP_UTF8));

	if ((JOIN_NAME == "") || (JOIN_BIRTH == "")) {
		MessageBox(_T("이름 또는 생년월일을 입력해주세요"), _T("SIGN UP"), MB_ICONWARNING);
	}
	else {
		// 모션 등록 버튼 클릭시 파이썬 파일 실행
		PyObject* pName, * pModule, * pFunc, * pValue, *pArg, * objectsRepresentation;
		Py_Initialize();
		pName = PyUnicode_FromString("SignupMotion"); // testFile.py를 PyObject로 생성한다.
		pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import한다.
		pFunc = PyObject_GetAttrString(pModule, "motion"); // 실행할 함수인 motion을 PyObject에 전달한다.

		pArg = Py_BuildValue("(s,s)", name, birth); // 배열에 매개변수 저장
		pValue = PyObject_CallObject(pFunc, pArg); // pFunc에 매개변수를 전달해서 실행한다..

		objectsRepresentation = PyObject_Repr(pValue); // 객체를 문자열로 표현한다.
		PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩한다.
		std::string result = PyBytes_AsString(str); // string으로 변환하여 준다.
		std::cout << result;

		PyRun_SimpleString("import cv2\n"
			               "cv2.destroyAllWindows()\n");

		//Py_Finalize();

		delete[] name;
		delete[] birth;

		int tmp = stoi(result);

		if (tmp == 20) {
			if (IDOK == MessageBox(_T("가입 완료"), _T("SIGN UP"), MB_ICONINFORMATION)) {
				LOGINDlg logindlg;
				PostMessage(WM_CLOSE); // 회원가입 다이얼로그 닫음
				logindlg.DoModal();	   // 로그인 다이얼로그 오픈
			}
		}
	}
}




void SIGNUPDlg::OnBnClickedButton2()
{
	LOGINDlg logindlg;
	PostMessage(WM_CLOSE); // 회원가입 다이얼로그 닫음
	logindlg.DoModal();	   // 로그인 다이얼로그 오픈
}
