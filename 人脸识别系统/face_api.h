#pragma once
#include "arcsoft_face_sdk.h"
#include "amcomdef.h"
#include "asvloffscreen.h"
#include "merror.h"
#include <direct.h>
#include <iostream>  
#include <stdarg.h>
#include <string>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;
#pragma comment(lib, "libarcsoft_face_engine.lib")

#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; } 
#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; } 

#define APPID "2Faex38JmTDEbFc1bwvaWh8Mj17JNbDq6Y174yL9rLcc"

//64
#define SDKKey  "8LJqeAmH6wsjcdBBMt6E1WRjwNoXSvycf1ehVngD1epB"

BOOL faceInit(MHandle* handle);

float faceCompare(MHandle faceModel, Mat &img1, Mat &img2);