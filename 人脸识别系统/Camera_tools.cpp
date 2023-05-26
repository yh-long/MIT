#include "pch.h"
#include "Camera_tools.h"



void referCamera(VideoCapture *cap,CWnd* pWnd, Postion_XY camera_pos)  // 获取主窗口指针)
{
	Mat frame; //opencv中表示图片数据
	*cap >> frame;
	imwrite(FILE_NAME, frame); // 保存图片
	HBITMAP video = (HBITMAP)LoadImage(0, L"./video/video.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	HDC hDC = ::GetDC(pWnd->GetSafeHwnd());  // 获取主窗口DC句柄
	//创建内存DC
	HDC HMemDC = CreateCompatibleDC(hDC);
	// 将位图对象选入内存DC
	SelectObject(HMemDC, video);

	// 将位图绘制到窗口上
	BitBlt(hDC, camera_pos.x, camera_pos.y, camera_pos.width, camera_pos.height, HMemDC, 0, 0, SRCCOPY);

	// 释放资源
	DeleteDC(HMemDC);
	DeleteObject(video);
}

void MatToCImage(Mat& mat, CImage& cimage)
{
	if (0 == mat.total())
	{
		return;
	}
	int nChannels = mat.channels();
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = mat.cols;
	int nHeight = mat.rows;
	//重建cimage
	cimage.Destroy();
	cimage.Create(nWidth, nHeight, 8 * nChannels);
	//拷贝数据
	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();		//指向数据区的指针
	int nStep = cimage.GetPitch();					//每行的字节数,注意这个返回值有正有负
	if (1 == nChannels)								//对于单通道的图像需要初始化调色板
	{
		RGBQUAD* rgbquadColorTable;
		int nMaxColors = 256;
		rgbquadColorTable = new RGBQUAD[nMaxColors];
		cimage.GetColorTable(0, nMaxColors, rgbquadColorTable);
		for (int nColor = 0; nColor < nMaxColors; nColor++)
		{
			rgbquadColorTable[nColor].rgbBlue = (uchar)nColor;
			rgbquadColorTable[nColor].rgbGreen = (uchar)nColor;
			rgbquadColorTable[nColor].rgbRed = (uchar)nColor;
		}
		cimage.SetColorTable(0, nMaxColors, rgbquadColorTable);
		delete[]rgbquadColorTable;
	}
	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				*(pucImage + nRow * nStep + nCol) = pucRow[nCol];
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					*(pucImage + nRow * nStep + nCol * 3 + nCha) = pucRow[nCol * 3 + nCha];
				}
			}
		}
	}
}

void CImageToMat(CImage& cimage, Mat& mat)
{
	if (true == cimage.IsNull())
	{
		return;
	}
	int nChannels = cimage.GetBPP() / 8;
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = cimage.GetWidth();
	int nHeight = cimage.GetHeight();
	//重建mat
	if (1 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC1);
	}
	else if (3 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC3);
	}
	//拷贝数据
	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();		//指向数据区的指针
	int nStep = cimage.GetPitch();					//每行的字节数,注意这个返回值有正有负
	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				pucRow[nCol] = *(pucImage + nRow * nStep + nCol);
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					pucRow[nCol * 3 + nCha] = *(pucImage + nRow * nStep + nCol * 3 + nCha);
				}
			}
		}
	}
}

void referCamera_simple(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera) {
	Mat frame; //opencv中表示图片数据
	*cap >> frame;
	imwrite(FILE_NAME, frame); // 保存图片
	CImage image;	
	image.Load(_T("./video/video.bmp"));	
	CDC* pDc = m_Camera.GetDC();
	image.BitBlt(pDc->m_hDC, 0, 0);
	ReleaseDC(pWnd->m_hWnd, pDc->m_hDC);
}

void referCamera_simple1(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera) {
	Mat frame; //opencv中表示图片数据
	*cap >> frame;
	CImage image;
	MatToCImage(frame, image);
	CDC* pDc = m_Camera.GetDC();
	image.BitBlt(pDc->m_hDC, 0, 0);
	ReleaseDC(pWnd->m_hWnd, pDc->m_hDC);
}

void Camera_Photo(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera)
{
	Mat frame; //opencv中表示图片数据
	*cap >> frame;
	imwrite(FILE_TMP, frame); // 保存图片
	CImage image;
	MatToCImage(frame, image);
	CDC* pDc = m_Camera.GetDC();
	image.BitBlt(pDc->m_hDC, 0, 0);
	ReleaseDC(pWnd->m_hWnd, pDc->m_hDC);
}

