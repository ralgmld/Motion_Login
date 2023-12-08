// LOGINHOMEDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Motion.h"
#include "afxdialogex.h"
#include "LOGINHOMEDlg.h"
#include "LOGINDlg.h"
#include "SIGNUPDlg.h"
#include "includePython.h"
#include "string"
#include "stdio.h"
#include "iostream"
#include "vector"
#include "atlstr.h"
#include "object.h"

#include "mysql.h"
#include <WinSock2.h>
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

#define DB_SERVER_IP "localhost"  // mysql 서버 이름
#define DB_NAME "users"     // mysql DB 네임
#define DB_ID "root"		      // mysql 접속 id
#define DB_PWD "mysql"			  // mysql 접속 password


// LOGINHOMEDlg 대화 상자

IMPLEMENT_DYNAMIC(LOGINHOMEDlg, CDialogEx)

LOGINHOMEDlg::LOGINHOMEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGINHOME, pParent)
{

}

LOGINHOMEDlg::~LOGINHOMEDlg()
{
}

void LOGINHOMEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOTIONCH, MotionChangeBtn);
	DDX_Control(pDX, IDC_WEB, WebBtn);
}


BEGIN_MESSAGE_MAP(LOGINHOMEDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_WEB, &LOGINHOMEDlg::OnBnClickedWeb)
	ON_BN_CLICKED(IDC_MOTIONCH, &LOGINHOMEDlg::OnBnClickedMotionch)
	ON_BN_CLICKED(IDC_MOTIONDEL, &LOGINHOMEDlg::OnBnClickedMotiondel)
END_MESSAGE_MAP()


// LOGINHOMEDlg 메시지 처리기
BOOL LOGINHOMEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("HOME")); // 타이틀바 제목 변경

	MotionChangeBtn.LoadBitmaps(IDB_BITMAP1, NULL, NULL, NULL); // 로그인 모션인증 버튼에 이미지 입히기
	MotionChangeBtn.SizeToContent();

	WebBtn.LoadBitmaps(IDB_BITMAP2, NULL, NULL, NULL); // 로그인 모션인증 버튼에 이미지 입히기
	WebBtn.SizeToContent();

	m_brush1.CreateSolidBrush(RGB(0, 38, 77));

	return TRUE;
}

BOOL LOGINHOMEDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;
}


HBRUSH LOGINHOMEDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(0, 38, 77));  // 아이디, 생년월일 STATIC TEXT 배경색 지정
		return m_brush1;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void LOGINHOMEDlg::OnBnClickedWeb()
{	
	/*CString NAME;
	CString BIRTH;

	NAME = ((LOGINDlg*)GetParent())->LOGIN_NAME;
	BIRTH = ((LOGINDlg*)GetParent())->LOGIN_BIRTH;

	char* name;
	char* birth;
	char* PASSWORD;

	int name_size = NAME.GetLength();
	name_size = (name_size * 3) + 1;
	name = new char[name_size];
	strcpy_s(name, name_size, CW2A(NAME, CP_UTF8));

	int birth_size = BIRTH.GetLength();
	birth_size = (birth_size * 3) + 1;
	birth = new char[birth_size];
	strcpy_s(birth, birth_size, CW2A(BIRTH, CP_UTF8));

	// 파이썬 캠 오픈하여 플래그값 비교
	PyObject* pName, * pModule, * pFunc, * pValue, * pArg, * objectsRepresentation;
	Py_Initialize();
	pName = PyUnicode_FromString("Web"); // testFile.py를 PyObject로 생성한다.
	pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import한다.
	pFunc = PyObject_GetAttrString(pModule, "web"); // 실행할 함수인 motion을 PyObject에 전달한다.

	pArg = Py_BuildValue("(s,s)", name, birth); // 배열에 매개변수 저장
	pValue = PyObject_CallObject(pFunc, pArg); // pFunc에 매개변수를 전달해서 실행한다..

	objectsRepresentation = PyObject_Repr(pValue); // 객체를 문자열로 표현한다.
	PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩한다.
	std::string result = PyBytes_AsString(str); // string으로 변환하여 준다.
	std::cout << result;*/

	// 버튼 클릭 시 웹 접속
	ShellExecute(this->m_hWnd, TEXT("open"), TEXT("chrome.exe"), TEXT("https://www.mokpo.ac.kr/index.9is"), NULL, SW_SHOW);
}


void LOGINHOMEDlg::OnBnClickedMotionch()
{
	CString NAME;
	CString BIRTH;

	NAME = ((LOGINDlg*)GetParent())->LOGIN_NAME;
	BIRTH = ((LOGINDlg*)GetParent())->LOGIN_BIRTH;

	char* name;
	char* birth;

	int name_size = NAME.GetLength();
	name_size = (name_size * 3) + 1;
	name = new char[name_size];
	strcpy_s(name, name_size, CW2A(NAME, CP_UTF8));

	int birth_size = BIRTH.GetLength();
	birth_size = (birth_size * 3) + 1;
	birth = new char[birth_size];
	strcpy_s(birth, birth_size, CW2A(BIRTH, CP_UTF8));

	PyObject * pName, * pModule, * pFunc, * pValue, * pArg, * objectsRepresentation;
	Py_Initialize();
	pName = PyUnicode_FromString("MotionChange"); // testFile.py를 PyObject로 생성한다.
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

	delete[] name;
	delete[] birth;

	int tmp = stoi(result);

	if (tmp == 20) {
		MessageBox(_T("모션 수정 성공"), _T("알림"), MB_ICONINFORMATION);
	}
	
	//Py_Finalize();
}


void LOGINHOMEDlg::OnBnClickedMotiondel()
{
	int tmp = 0;

	CString NAME;
	CString BIRTH;

	NAME = ((LOGINDlg*)GetParent())->LOGIN_NAME;
	BIRTH = ((LOGINDlg*)GetParent())->LOGIN_BIRTH;

	char* name;
	char* birth;

	int name_size = NAME.GetLength();
	name_size = (name_size * 3) + 1;
	name = new char[name_size];
	strcpy_s(name, name_size, CW2A(NAME, CP_UTF8));

	int birth_size = BIRTH.GetLength();
	birth_size = (birth_size * 3) + 1;
	birth = new char[birth_size];
	strcpy_s(birth, birth_size, CW2A(BIRTH, CP_UTF8));

	PyObject* pName, * pModule, * pFunc, * pValue, * pArg, * objectsRepresentation;
	Py_Initialize();
	pName = PyUnicode_FromString("MotionDel"); // testFile.py를 PyObject로 생성한다.
	pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import한다.
	pFunc = PyObject_GetAttrString(pModule, "motion_del"); // 실행할 함수인 motion을 PyObject에 전달한다.

	pArg = Py_BuildValue("(s,s)", name, birth); // 배열에 매개변수 저장
	pValue = PyObject_CallObject(pFunc, pArg); // pFunc에 매개변수를 전달해서 실행한다..

	objectsRepresentation = PyObject_Repr(pValue); // 객체를 문자열로 표현한다.
	PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩한다.
	std::string result = PyBytes_AsString(str); // string으로 변환하여 준다.
	std::cout << result;

	tmp = stoi(result);

	if (tmp == 0) {
		MessageBox(_T("모션 삭제 완료"), _T("알림"), MB_ICONINFORMATION);
	}
}
