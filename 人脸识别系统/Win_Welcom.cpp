// Win_Welcom.cpp: 实现文件
//

#include "pch.h"
#include "人脸识别系统.h"
#include "afxdialogex.h"
#include "Win_Welcom.h"


// Win_Welcom 对话框

IMPLEMENT_DYNAMIC(Win_Welcom, CDialogEx)

Win_Welcom::Win_Welcom(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG_WELCOM, pParent)
{

}

Win_Welcom::~Win_Welcom()
{
}

void Win_Welcom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Win_Welcom, CDialogEx)
END_MESSAGE_MAP()


// Win_Welcom 消息处理程序
