#pragma once
#include "afxdialogex.h"

#include "ButtonPNG.h"
#include "Camera_tools.h"
#include "face_api.h"
#include "Win_Welcom.h"

#include <mmsystem.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib,"winmm.lib")
using namespace cv;

static VideoCapture cap;//摄像头
// Win_Register 对话框

class Win_Register : public CDialogEx
{
	DECLARE_DYNAMIC(Win_Register)

public:
	Win_Register(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Win_Register();
	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG_REFISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton();
	CImage m_img_bg;
	ButtonPNG m_btn_mouse;
	CEdit m_text_name;
	CStatic m_snowBG;
	afx_msg void OnPaint();
	HBITMAP m_snows[16];
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_Camera;
	
};
