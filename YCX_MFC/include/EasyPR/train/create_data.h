#ifndef EASYPR_CREATE_DATA_H_
#define EASYPR_CREATE_DATA_H_

#include "opencv2/opencv.hpp"
#include "config.h"

using namespace cv;
using namespace std;

/*! \namespace easypr
Namespace where all the C++ EasyPR functionality resides
*/
namespace easypr
{
	// ��ȡͼ��߽���ɫ��ƽ��ֵ
	int getBoderColor(Mat img);
	// shift an image
	Mat translateImg(Mat img, int offsetx, int offsety, int bk = 0);
	// rotate an image
	Mat rotateImg(Mat source, float angle, int bk = 0);
	// crop the image
	Mat cropImg(Mat src, int x, int y, int shift, int bk = 0);
	// �Ը����ַ�ͼ����м��α任(ƽ��/��ת)���Ӷ��˹��ϳɵõ��µ�ͼ������ѵ��
	Mat generateSyntheticImage(const Mat& image, int use_swap = 1);

} /*! \namespace easypr*/

#endif  // EASYPR_CREATE_DATA_H_