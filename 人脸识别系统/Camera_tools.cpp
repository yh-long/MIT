#include "pch.h"
#include "Camera_tools.h"



void referCamera(VideoCapture *cap,CWnd* pWnd, Postion_XY camera_pos)  // ��ȡ������ָ��)
{
	Mat frame; //opencv�б�ʾͼƬ����
	*cap >> frame;
	imwrite(FILE_NAME, frame); // ����ͼƬ
	HBITMAP video = (HBITMAP)LoadImage(0, L"./video/video.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	HDC hDC = ::GetDC(pWnd->GetSafeHwnd());  // ��ȡ������DC���
	//�����ڴ�DC
	HDC HMemDC = CreateCompatibleDC(hDC);
	// ��λͼ����ѡ���ڴ�DC
	SelectObject(HMemDC, video);

	// ��λͼ���Ƶ�������
	BitBlt(hDC, camera_pos.x, camera_pos.y, camera_pos.width, camera_pos.height, HMemDC, 0, 0, SRCCOPY);

	// �ͷ���Դ
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
	//�ؽ�cimage
	cimage.Destroy();
	cimage.Create(nWidth, nHeight, 8 * nChannels);
	//��������
	uchar* pucRow;									//ָ������������ָ��
	uchar* pucImage = (uchar*)cimage.GetBits();		//ָ����������ָ��
	int nStep = cimage.GetPitch();					//ÿ�е��ֽ���,ע���������ֵ�����и�
	if (1 == nChannels)								//���ڵ�ͨ����ͼ����Ҫ��ʼ����ɫ��
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
	//�ؽ�mat
	if (1 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC1);
	}
	else if (3 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC3);
	}
	//��������
	uchar* pucRow;									//ָ������������ָ��
	uchar* pucImage = (uchar*)cimage.GetBits();		//ָ����������ָ��
	int nStep = cimage.GetPitch();					//ÿ�е��ֽ���,ע���������ֵ�����и�
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
	Mat frame; //opencv�б�ʾͼƬ����
	*cap >> frame;
	imwrite(FILE_NAME, frame); // ����ͼƬ
	CImage image;	
	image.Load(_T("./video/video.bmp"));	
	CDC* pDc = m_Camera.GetDC();
	image.BitBlt(pDc->m_hDC, 0, 0);
	ReleaseDC(pWnd->m_hWnd, pDc->m_hDC);
}

void referCamera_simple1(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera) {
	Mat frame; //opencv�б�ʾͼƬ����
	*cap >> frame;
	CImage image;
	MatToCImage(frame, image);
	CDC* pDc = m_Camera.GetDC();
	image.BitBlt(pDc->m_hDC, 0, 0);
	ReleaseDC(pWnd->m_hWnd, pDc->m_hDC);
}

void Camera_Photo(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera)
{
	Mat frame; //opencv�б�ʾͼƬ����
	*cap >> frame;
	imwrite(FILE_TMP, frame); // ����ͼƬ
	CImage image;
	MatToCImage(frame, image);
	CDC* pDc = m_Camera.GetDC();
	image.BitBlt(pDc->m_hDC, 0, 0);
	ReleaseDC(pWnd->m_hWnd, pDc->m_hDC);
}

