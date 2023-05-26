// Win_Home.cpp: 实现文件
//

#include "pch.h"
#include "人脸识别系统.h"
#include "afxdialogex.h"
#include "Win_Home.h"
#include <graphics.h>

// Win_Home 对话框

IMPLEMENT_DYNAMIC(Win_Home, CDialogEx)

Win_Home::Win_Home(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG_Home, pParent)
{

}

Win_Home::~Win_Home()
{
}

BOOL Win_Home::OnInitDialog()
{
	CDialog::OnInitDialog();

	char fileName[256];
	sprintf_s(fileName, sizeof(fileName), "./user/%s-%s-%d.jpg", m_job, m_username, m_yanzhi);
	IMAGE img1, img2;
	loadimage(&img1, CString(fileName), 200, 150, true);
	loadimage(&img2, L"./res/yz2.jpg");
	imgR.Load(CString(fileName));
	m_HEAD.SetBitmap(imgR);

	CFont font;
	font.CreatePointFont(200, L"华文行楷", NULL);

	m_text_name.SetFont(&font);
	m_text_name.SetWindowTextW(CString(m_username));

	m_text_yanzhi.SetFont(&font);
	CString yanzhi;
	yanzhi.Format(L"颜值：%d", m_yanzhi);
	m_text_yanzhi.SetWindowTextW(yanzhi);

	m_text_job.SetFont(&font);
	m_text_job.SetWindowTextW(CString(m_job));

	m_text_b.SetFont(&font);;
	m_text_b.SetWindowTextW(L"B币：8000");

	m_text_qq.SetFont(&font);
	m_text_qq.SetWindowTextW(L"QQ：123456789");

	m_leftbg.Load(L"./res/buttonBg.bmp");
	m_btn_video.Init(IDB_PAUSE_PNG,4,BTN_TYPE_NORMAL);

	videoPlayerInit(&m_player);
	return 0;
}

void Win_Home::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEST_NAME, m_text_name);
	DDX_Control(pDX, IDC_TEXT_YANZHI, m_text_yanzhi);
	DDX_Control(pDX, IDC_TEXT_JOB, m_text_job);
	DDX_Control(pDX, IDC_TEXT_B, m_text_b);
	DDX_Control(pDX, IDC_TEXT_QQQUN, m_text_qq);
	DDX_Control(pDX, IDC_BTN_VIDEO, m_btn_video);
	DDX_Control(pDX, IDC_HEAD, m_HEAD);
}


BEGIN_MESSAGE_MAP(Win_Home, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_VIDEO, &Win_Home::OnBnClickedBtnVideo)
END_MESSAGE_MAP()


// Win_Home 消息处理程序


void Win_Home::OnPaint()
{
	drawPicOnPait(&m_leftbg, this, 450, 0);
}


void Win_Home::OnBnClickedBtnVideo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_player_status == 0) {
		//播放
		m_player.hwnd = GetDlgItem(IDC_MOVIE)->GetSafeHwnd();
		videoPlayerPlay(&m_player, "");
		m_player_status = 1;
		m_btn_video.Init(IDB_PLAY_PNG, 4, BTN_TYPE_NORMAL);
	}
	else if (m_player_status == 1) {
		//暂停
		videoPlayerPause(&m_player);
		m_player_status = 2;
		m_btn_video.Init(IDB_PAUSE_PNG, 4, BTN_TYPE_NORMAL);
	}
	else {
		//继续播放
		videoPlayerPause(&m_player);
		m_player_status = 1;
		m_btn_video.Init(IDB_PLAY_PNG, 4, BTN_TYPE_NORMAL);
	}
}
