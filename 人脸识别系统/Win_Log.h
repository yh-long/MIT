#pragma once
#include "afxdialogex.h"

#include"ButtonPNG.h"
// Win_Log 对话框
#include "Camera_tools.h"
#include "face_api.h"
#include "Win_Welcom.h"

#include <Windows.h>
#include <mmsystem.h>
#include <filesystem>
#include <opencv2/opencv.hpp>

#pragma comment(lib,"winmm.lib")
using namespace cv;

extern MHandle faceModel;
static VideoCapture cap_login;//摄像头


class Win_Log : public CDialogEx
{
	DECLARE_DYNAMIC(Win_Log)

public:
	Win_Log(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Win_Log();
	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	ButtonPNG m_btn_ac;
	CImage m_img_bg;

	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	HBITMAP m_snows[16] = { 0 };
	CBitmap bitmap[16];
	CStatic m_snowBG;
	
	afx_msg void OnBnClickedButton();
	
	CStatic m_Camera;

	char m_job[64];
	char m_username[64];
	int m_yanzhi;

	bool m_logined;
};
