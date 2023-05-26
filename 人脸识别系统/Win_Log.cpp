// Win_Log.cpp: 实现文件
//

#include "pch.h"
#include "人脸识别系统.h"
#include "afxdialogex.h"
#include "Win_Log.h"


// Win_Log 对话框

IMPLEMENT_DYNAMIC(Win_Log, CDialogEx)

Win_Log::Win_Log(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG_LOGIN, pParent)
{
	
}

Win_Log::~Win_Log()
{
}

BOOL Win_Log::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//
	LoadPicture(m_img_bg, IDB_FACE_PNG);
	m_btn_ac.Init(IDB_MOUSE_PNG, 4, BTN_TYPE_NORMAL);

	CString name;
	//char name[256]
	for (int i = 0; i < 16; i++) {
		//sprintf_s(name, "res/snow/snow_%d.bmp", i);
		name.Format(L"./res/snow/snow_%d.bmp", i);
		m_snows[i] = (HBITMAP)LoadImage(0, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
	//设置定时器
	SetTimer(1, 30, NULL);

	::MoveWindow(m_btn_ac.m_hWnd, 165, 420, 90, 50, 1);
	::MoveWindow(m_snowBG.m_hWnd, 440, 0, 640, 609, 1);
	::MoveWindow(m_Camera.m_hWnd, 440, 60, 640, 609, 1);
	return 0;
}

void Win_Log::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON, m_btn_ac);
	DDX_Control(pDX, IDC_SNOW, m_snowBG);
	DDX_Control(pDX, IDC_CAMERA, m_Camera);
}


BEGIN_MESSAGE_MAP(Win_Log, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	
	ON_BN_CLICKED(IDC_BUTTON, &Win_Log::OnBnClickedButton)
	
END_MESSAGE_MAP()

// Win_login 消息处理程序


void Win_Log::OnPaint()
{
	drawPicOnPait(&m_img_bg, this, 0, 0);
}

bool faceCheck(char* userName) {
	//
	vector<CString> vctPath;
	WIN32_FIND_DATA filedata;
	HANDLE file = FindFirstFile(L"./users/*.jpg", &filedata);
	if (file!=INVALID_HANDLE_VALUE) {
		vctPath.push_back(filedata.cFileName);
		while (FindNextFileW(file,&filedata))
		{
			vctPath.push_back(filedata.cFileName);
		}
	}
	
	Mat img1 = imread(FILE_TMP);
	if (vctPath.empty()) return false;
	for (int i = 0; i < vctPath.size(); i++) {
		USES_CONVERSION;//将CString转成char
		CString vctname= vctPath[i];
		char* otherName = T2A(vctname);
		char name[256];
		sprintf_s(name, sizeof(name), "./users/%s", otherName);
		Mat img2 = imread(name);
		float ret=faceCompare(faceModel, img1, img2);
		if (ret >= 0.92) {
			string tmpStr = otherName;
			string nameStr = tmpStr.substr(0, tmpStr.length() - 4);
			strcpy(userName, nameStr.c_str());
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Win_Log::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int snowIndex = 0;
	static int count = 0;
	static char userName[256] = "";
	static bool success = false;
	if (nIDEvent == 1) {
		m_snowBG.SetBitmap(m_snows[snowIndex]);
		snowIndex = (snowIndex + 1) % 16;
	}
	else if (nIDEvent == 2) {
		CWnd* pWnd = GetForegroundWindow();  // 获取当前窗口指针
		referCamera_simple1(&cap_login, pWnd, m_Camera);
		count++;
		if (count == 10) {
			Camera_Photo(&cap_login, pWnd, m_Camera);
			//人脸识别
			if (faceCheck(userName)) {
				//登录音乐
				mciSendString(L"play ./res/login.mp3", 0, 0, 0);
				success = true;
			}
		}
		else if (count == 20) {
			count = 0;
			KillTimer(2);
			cap_login.release();
			//识别成功或失败
			if (success) {
				strcpy(m_job,strtok(userName,"-"));
				strcpy(m_username, strtok(NULL, "-"));
				m_yanzhi = atoi(strtok(NULL, "-"));
				m_logined = true;
				CDialog::OnOK();
			}
			else {
				MessageBox(L"登录失败!");
				SetTimer(1, 100, NULL);
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void Win_Log::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	cap_login.open(0);
	HBITMAP pic= (HBITMAP)LoadImage(0, L"./res/wall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_snowBG.SetBitmap(pic);

	SetTimer(2, 100, NULL);
}

