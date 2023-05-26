
// 人脸识别系统Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "人脸识别系统.h"
#include "人脸识别系统Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C人脸识别系统Dlg 对话框



C人脸识别系统Dlg::C人脸识别系统Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C人脸识别系统Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON, m_btn_login);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_AC);
}

BEGIN_MESSAGE_MAP(C人脸识别系统Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, &C人脸识别系统Dlg::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON1, &C人脸识别系统Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// C人脸识别系统Dlg 消息处理程序

BOOL C人脸识别系统Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	LoadPicture(m_img_BG, IDB_BG_PNG);
	m_btn_login.Init(login, 4, BTN_TYPE_NORMAL);
	m_btn_AC.Init(regis, 4, BTN_TYPE_NORMAL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C人脸识别系统Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C人脸识别系统Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{ 
		//CDialogEx::OnPaint();
		drawPicOnPait(&m_img_BG, this, 0, 0);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C人脸识别系统Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C人脸识别系统Dlg::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	Win_Log win_login;
	win_login.DoModal();
	if (win_login.m_logined) {
		Win_Welcom win_welcom;
		win_welcom.DoModal();
		Win_Home win_home;
		strcpy(win_home.m_username, win_login.m_username);
		strcpy(win_home.m_job, win_login.m_job);
		win_home.m_yanzhi = win_login.m_yanzhi;
		win_home.DoModal();
	}
}


void C人脸识别系统Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	Win_Register win_register;
	win_register.DoModal();
}
