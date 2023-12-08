// LOGINDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Motion.h"
#include "afxdialogex.h"
#include "LOGINDlg.h"
#include "SIGNUPDlg.h"
#include "LOGINHOMEDlg.h"
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
#define DB_NAME "motion"     // mysql DB 네임
#define DB_ID "root"		      // mysql 접속 id
#define DB_PWD "mysql"			  // mysql 접속 password


// LOGINDlg 대화 상자

IMPLEMENT_DYNAMIC(LOGINDlg, CDialogEx)

LOGINDlg::LOGINDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{
	m_loginico = AfxGetApp()->LoadIcon(IDI_LOGINICON);
}

LOGINDlg::~LOGINDlg()
{
}

void LOGINDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LoginMotion, LoginMotionBtn);
}


BEGIN_MESSAGE_MAP(LOGINDlg, CDialogEx)
//	ON_WM_CTLCOLOR()
ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_JOINBTN, &LOGINDlg::OnBnClickedJoinbtn)
ON_BN_CLICKED(IDC_LoginMotion, &LOGINDlg::OnBnClickedLoginmotion)
END_MESSAGE_MAP()


// LOGINDlg 메시지 처리기
BOOL LOGINDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("LOGIN")); // 타이틀바 제목 변경

	//LoginMotionBtn.Attach(((CBitmapButton*)GetDlgItem(IDC_LoginMotion))->m_hWnd);
	LoginMotionBtn.LoadBitmaps(IDB_BITMAP1, NULL, NULL, NULL); // 로그인 모션인증 버튼에 이미지 입히기
	LoginMotionBtn.SizeToContent();

	m_brush1.CreateSolidBrush(RGB(0, 38, 77));

	SetIcon(m_loginico, TRUE);
	SetIcon(m_loginico, FALSE);

	return TRUE;
}

BOOL LOGINDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255,255,255));

	return TRUE;
}


HBRUSH LOGINDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void LOGINDlg::OnBnClickedJoinbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SIGNUPDlg logindlg;
	PostMessage(WM_CLOSE); // 회원가입 다이얼로그 닫음
	logindlg.DoModal();	   // 로그인 다이얼로그 오픈
}


void LOGINDlg::OnBnClickedLoginmotion() // 모션인증 버튼시 동작할 내용 작성
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

//	CString LOGIN_NAME;
//	CString LOGIN_BIRTH;
	int i = 0;

	GetDlgItemText(IDC_LoginName, LOGIN_NAME);
	GetDlgItemText(IDC_LoginBirth, LOGIN_BIRTH);

	int name_size = LOGIN_NAME.GetLength();
	name_size = (name_size * 3) + 1;
	name = new char[name_size];
	strcpy_s(name, name_size, CW2A(LOGIN_NAME, CP_UTF8));

	int birth_size = LOGIN_BIRTH.GetLength();
	birth_size = (birth_size * 3) + 1;
	birth = new char[birth_size];
	strcpy_s(birth, birth_size, CW2A(LOGIN_BIRTH, CP_UTF8));
	
	if ((LOGIN_NAME == "") || (LOGIN_BIRTH == "")) {
		MessageBox(_T("이름 또는 생년월일을 입력해주세요"), _T("LOGIN UP"), MB_ICONWARNING);
	}

	// DB에서 사용자가 입력한 이름과 생년월일 존재하는지 비교
	MYSQL mysql;
	MYSQL_ROW m_row;
	MYSQL_RES* m_res;

	mysql_init(&mysql);  // DB 연결
	if (mysql_real_connect(&mysql, DB_SERVER_IP, DB_ID, DB_PWD, DB_NAME, 3306, NULL, 0) == NULL)
		return;
	else
		mysql_query(&mysql, "set names euckr");

	// 쿼리 저장할 변수 선언 및 쿼리 저장
	char* query;
	query = "SELECT * FROM motion_info";

	// 쿼리 실행
	mysql_query(&mysql, query);
	m_res = mysql_store_result(&mysql);


	if (m_res == NULL) {
		TRACE(_T("내용 없음\n"));
	}
	else {
		while ((m_row = mysql_fetch_row(m_res)) != NULL) {
			i = 0;

			// 쿼리 결과 값으로 가져온 이름, 생년월일 값을 tmp1, tmp2에 저장
			CString name(m_row[0]);
			CString birth(m_row[1]);

			// DB의 id,pwd 값 tmp1,tmp2와 사용자가 압력한 ID,PWD 값을 비교함
			if (name == LOGIN_NAME && birth == LOGIN_BIRTH) {
				i = 1;
				break;
			}
			else {
				i = 2;   // 값이 다르다면 i에 2 대입
			}
		}
		if (i == 1) {

			// 파이썬 캠 오픈하여 플래그값 비교
			PyObject* pName, * pModule, * pFunc, * pValue, * pArg, * objectsRepresentation;
			Py_Initialize();
			pName = PyUnicode_FromString("LoginMotion"); // testFile.py를 PyObject로 생성한다.
			pModule = PyImport_Import(pName); // 생성한 PyObject pName을 import한다.
			pFunc = PyObject_GetAttrString(pModule, "motion"); // 실행할 함수인 motion을 PyObject에 전달한다.

			pArg = Py_BuildValue("(s,s)", name, birth); // 배열에 매개변수 저장
			pValue = PyObject_CallObject(pFunc, pArg); // pFunc에 매개변수를 전달해서 실행한다..

			objectsRepresentation = PyObject_Repr(pValue); // 객체를 문자열로 표현한다.
			PyObject* str = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "~E~"); // 객체를 인코딩한다.
			std::string result = PyBytes_AsString(str); // string으로 변환하여 준다.
			std::cout << result;

			//tmp = PyLong_AsLong(pValue);

			PyRun_SimpleString("import cv2\n"
							   "cv2.destroyAllWindows()\n");

			//Py_Finalize();

			mysql_close(&mysql);  // DB 접속 종료
			delete[] name;
			delete[] birth;

			int tmp = stoi(result);

			if (tmp == 10) {
				if (MessageBox(_T("로그인 성공"), _T("알림"), MB_ICONINFORMATION)) {
					LOGINHOMEDlg logindlg;
					PostMessage(WM_CLOSE); // 로그인 다이얼로그 닫음
					logindlg.DoModal();	   // 홈 다이얼로그 오픈
				}
			}
			else if (tmp == 400) {
				MessageBox(_T("로그인 실패"), _T("알림"), MB_ICONINFORMATION);

			}
		}
		
		if (i == 2) {       // ID와 PWD가 일치하지 않다면
			MessageBox(_T("회원정보가 없습니다."), _T("알림"), MB_ICONWARNING);   // 로그인 실패 알림 창 띄우기
			SetDlgItemText(IDC_LoginName, L"");    // ID와 PWD 입력 칸 초기화
			SetDlgItemText(IDC_LoginBirth, L"");
		}



	}

}
