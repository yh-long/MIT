#pragma once
#include "afxdialogex.h"
#include "Win_Home.h"

// Win_Welcom 对话框

class Win_Welcom : public CDialogEx
{
	DECLARE_DYNAMIC(Win_Welcom)

public:
	Win_Welcom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Win_Welcom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG_WELCOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
