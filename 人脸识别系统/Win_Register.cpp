// Win_Register.cpp: 实现文件
//

#include "pch.h"
#include "人脸识别系统.h"
#include "afxdialogex.h"
#include "Win_Register.h"

#define FILE_NAME "./video/video.bmp"
extern MHandle faceModel;//人脸识别模块

// Win_Register 对话框

IMPLEMENT_DYNAMIC(Win_Register, CDialogEx)

Win_Register::Win_Register(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG_REFISTER, pParent)
{
	
}

Win_Register::~Win_Register()
{
}

BOOL Win_Register::OnInitDialog()
{
	CDialog::OnInitDialog();
	LoadPicture(m_img_bg,IDB_FACE_PNG);
	m_btn_mouse.Init(IDB_MOUSE_PNG,4,BTN_TYPE_NORMAL);
	CString name;
	for (int i = 0; i < 16; i++) {
		name.Format(L"./res/snow/snow_%d.bmp", i);
		m_snows[i] = (HBITMAP)LoadImage(0, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	//定时器
	SetTimer(1, 100, NULL);

	CFont font;
	font.CreatePointFont(200, L"华文行楷", NULL);
	m_text_name.SetFont(&font);

	::MoveWindow(m_snowBG.m_hWnd, 440, 0, 640, 609, 1);
	::MoveWindow(m_Camera.m_hWnd, 440, 60, 640, 609, 1);
	return 0;
}

void Win_Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON, m_btn_mouse);
	DDX_Control(pDX, IDC_EDIT1, m_text_name);
	DDX_Control(pDX, IDC_SNOW, m_snowBG);
	DDX_Control(pDX, IDC_CAP, m_Camera);
}


BEGIN_MESSAGE_MAP(Win_Register, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON, &Win_Register::OnBnClickedButton)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Win_Register 消息处理程序


void Win_Register::OnBnClickedButton()
{
	if (m_text_name.GetWindowTextLength()==0) {
		MessageBox(L"请输入用户名！");
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);//关闭定时器1
	//打开摄像头
	cap.open(0);

	HBITMAP pic_wall = (HBITMAP)LoadImage(0, L"./res/wall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_snowBG.SetBitmap(pic_wall);

	SetTimer(2, 100, NULL);
}


void Win_Register::OnPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	drawPicOnPait(&m_img_bg, this, 0, 0);
}


void Win_Register::OnTimer(UINT_PTR nIDEvent)
{
	static int snowIndex = 0;
	static int cout = 0;
	if (nIDEvent == 1) {
		m_snowBG.SetBitmap(m_snows[snowIndex]);
		snowIndex = (snowIndex + 1) % 16;
	}
	else if (nIDEvent == 2) {
		//使用摄像头捕获
		CWnd* pWnd = GetForegroundWindow();  // 获取当前窗口指针
		/*Postion_XY camera_pos ={ 440, 80, 640, 609 };
		referCamera(&cap, pWnd, camera_pos);*/
		
		//referCamera_simple(&cap, pWnd, m_Camera);
		
		referCamera_simple1(&cap, pWnd, m_Camera);
		
		cout++;
		if (cout == 1) {
			mciSendString(L"play ./res/zhuche.mp3", 0, 0, 0);

		}
		else if (cout == 30) {
			//拍照
			cout = 0;
			Camera_Photo(&cap, pWnd, m_Camera);
			KillTimer(2);
			cap.release();

			Win_Welcom win;
			win.DoModal();
			CDialog::OnOK();

			//计算相似度
			
			Mat img1 = imread("tmp.jpg");
			Mat img2 = imread("./res/neijun.jpg");
			
			float xishu = faceCompare(faceModel, img1, img2);
			int yanzhi = xishu * 1000 + 80 + rand() % 15;
			if (yanzhi <= 0) {
				yanzhi = 60;
			}
			else if (yanzhi >= 100) {
				yanzhi = 99;
			}
			//生成职业
			const char* jobs[256] = { "猎杀者","执笔人","不死者" };
			//获取用户名
			CString editname;
			m_text_name.GetWindowTextW(editname);
			USES_CONVERSION;
			char* editname2 = T2A(editname);

			//format样式
			char cmd[1024];
			sprintf_s(cmd, "move tmp.jpg users\\%s-%s-%d.jpg", jobs[rand() % 3], editname2, yanzhi);
			system(cmd);

		}
		
	}

	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}