#ifndef CAMERA_TOOLS_H
#define CAMERA_TOOLS_H

#include <opencv2/opencv.hpp>

#define FILE_NAME "./video/video.bmp"
#define FILE_TMP "tmp.jpg"
#pragma once
using namespace cv;

typedef struct Postion_XY
{
	double x;
	double y;
	double width;
	double height;
};
//方案一更新捕获图片
void referCamera(VideoCapture *cap, CWnd* pos, Postion_XY camera_pos);
//方案二保存图片更新
void referCamera_simple(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera);
//方案三无图片更新
void referCamera_simple1(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera);

void Camera_Photo(VideoCapture* cap, CWnd* pWnd, CStatic& m_Camera);

void CImageToMat(CImage& cimage, Mat& mat);

void MatToCImage(Mat& mat, CImage& cimage);


#endif // !CAMERA_TOOLS_H
