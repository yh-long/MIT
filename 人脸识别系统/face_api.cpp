#include "pch.h"
#include "face_api.h"

//激活接口,需联网激活
BOOL faceInit(MHandle* handle) {
	//激活接口,需联网激活
	MRESULT res = ASFOnlineActivation((char*)APPID, (char*)SDKKey);
	if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res) {
		printf("激活失败\n");
		return FALSE;
	}	

	//获取激活文件信息
	ASF_ActiveFileInfo  activeFileInfo;
	res = ASFGetActiveFileInfo(&activeFileInfo);
	if (res != MOK) {
		printf("ASFGetActiveFileInfo fail: %d\n", res);
		return FALSE;
	}

	//初始化接口
	MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE | ASF_LIVENESS | ASF_IR_LIVENESS;
	res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, 30, 10, mask, handle);
	if (res != MOK) {
		printf("接口初始化失败\n");
		return FALSE;
	}
	return true;
}

void CutIplImage(Mat src, Mat dst, int x, int y) {
	Rect roi(x, y, dst.cols, dst.rows);//设置ROI
	//Mat roi_img = src(roi);
	src.copyTo(dst);
//	roi_img.release();
}

float faceCompare(MHandle handle, Mat& img1, Mat& img2)
{
	ASF_MultiFaceInfo detectedFaces1 = { 0 };//多人脸信息
	ASF_SingleFaceInfo SingleDetectedFaces1 = { 0 };//单人脸信息
	ASF_FaceFeature feature1 = { 0 };//人脸特征
	ASF_FaceFeature copyfeature1 = { 0 };//人脸特征
	
	/*传入图片测试*/
	//imwrite("test.jpg", img1);
	//imwrite("test.jpg", img2);

	//IplImage* cutImg1 = cvCreateImage(cvSize(img1->width - img1->width % 4, img1->height), IPL_DEPTH_8U, img1->nChannels);
	//CutIplImage(img1, cutImg1, 0, 0);

	Mat cutImg1(img1.rows, (img1.cols- img1.cols%4), CV_8UC3);
	CutIplImage(img1, cutImg1, 0, 0);
	

	MRESULT res;
	//人脸检测
	res = ASFDetectFaces(handle, cutImg1.cols, cutImg1.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg1.data, &detectedFaces1);
	//成功返回MOK，否则返回失败codes
	if (MOK == res)
	{
		if (detectedFaces1.faceRect != nullptr) {
			SingleDetectedFaces1.faceRect.left = detectedFaces1.faceRect[0].left;
			SingleDetectedFaces1.faceRect.top = detectedFaces1.faceRect[0].top;
			SingleDetectedFaces1.faceRect.right = detectedFaces1.faceRect[0].right;
			SingleDetectedFaces1.faceRect.bottom = detectedFaces1.faceRect[0].bottom;
			SingleDetectedFaces1.faceOrient = detectedFaces1.faceOrient[0];

			//res = ASFDetectFaces(handle, cutImg1->width, cutImg1->height, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg1->imageData, &detectedFaces1);
			//单人脸特征提取
			res = ASFFaceFeatureExtract(handle, cutImg1.cols, cutImg1.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg1.data, &SingleDetectedFaces1, &feature1);
			if (res == MOK)
			{
				//拷贝feature
				copyfeature1.featureSize = feature1.featureSize;
				copyfeature1.feature = (MByte*)malloc(feature1.featureSize);
				memset(copyfeature1.feature, 0, feature1.featureSize);
				memcpy(copyfeature1.feature, feature1.feature, feature1.featureSize);
			}
			else
				printf("ASFFaceFeatureExtract 1 fail: %d\n", res);
		}
	
	}
	else
		printf("ASFDetectFaces 1 fail: %d\n", res);

	//第二张人脸处理
	ASF_MultiFaceInfo	detectedFaces2 = { 0 };
	ASF_SingleFaceInfo SingleDetectedFaces2 = { 0 };
	ASF_FaceFeature feature2 = { 0 };
	//IplImage* cutImg2 = cvCreateImage(cvSize(img2->width - img2->width % 4, img2->height), IPL_DEPTH_8U, img2->nChannels);
	//CutIplImage(img2, cutImg2, 0, 0);
	Mat cutImg2(img2.rows, (img2.cols - img2.cols % 4), CV_8UC3);
	CutIplImage(img2, cutImg2, 0, 0);

	res = ASFDetectFaces(handle, cutImg2.cols, cutImg2.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg2.data, &detectedFaces2);
	
	if (MOK == res)
	{
		if (detectedFaces2.faceRect != nullptr) {
			SingleDetectedFaces2.faceRect.left = detectedFaces2.faceRect[0].left;
			SingleDetectedFaces2.faceRect.top = detectedFaces2.faceRect[0].top;
			SingleDetectedFaces2.faceRect.right = detectedFaces2.faceRect[0].right;
			SingleDetectedFaces2.faceRect.bottom = detectedFaces2.faceRect[0].bottom;
			SingleDetectedFaces2.faceOrient = detectedFaces2.faceOrient[0];

			//res = ASFDetectFaces(handle, cutImg1->width, cutImg1->height, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg1->imageData, &detectedFaces1);
			res = ASFFaceFeatureExtract(handle, cutImg2.cols, cutImg2.rows, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg2.data, &SingleDetectedFaces2, &feature2);
			if (MOK != res)
				printf("ASFFaceFeatureExtract 2 fail: %d\n", res);
		}
			
	}
	else
		printf("ASFDetectFaces 2 fail: %d\n", res);

	// 单人脸特征比对
	MFloat confidenceLevel;
	res = ASFFaceFeatureCompare(handle, &copyfeature1, &feature2, &confidenceLevel);
	if (res != MOK)
		confidenceLevel = -1;

	SafeFree(copyfeature1.feature);		//释放内存
	//cvReleaseImage(&cutImg1);
	//cvReleaseImage(&cutImg2);

	return confidenceLevel;
}


double compareImages(const cv::Mat& img1, const cv::Mat& img2) {
	if (img1.size != img2.size) {
		return -1.0;
	}
	cv::Mat diff;
	cv::absdiff(img1, img2, diff);
	cv::Mat squared_diff;
	cv::multiply(diff, diff, squared_diff);
	cv::Scalar sum = cv::sum(squared_diff);
	double mse = sum.val[0] / (img1.rows * img1.cols);
	return mse;
}
