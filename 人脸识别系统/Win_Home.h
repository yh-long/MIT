#pragma once
#include "afxdialogex.h"
#include "VideoPlayer.h"
#include "ButtonPNG.h"
// Win_Home 对话框

class Win_Home : public CDialogEx
{
	DECLARE_DYNAMIC(Win_Home)

public:
	Win_Home(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Win_Home();
	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG_Home };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	char m_job[64];
	char m_username[64];
	int m_yanzhi;
	CStatic m_text_name;
	CStatic m_text_yanzhi;
	CStatic m_text_job;
	CStatic m_text_b;
	CStatic m_text_qq;
	ButtonPNG m_btn_video;

	ATL::CImage imgR;
	ATL::CImage m_leftbg;
	CStatic m_HEAD;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnVideo();
private:
	VideoPlayer m_player;
	int m_player_status=0;
};
