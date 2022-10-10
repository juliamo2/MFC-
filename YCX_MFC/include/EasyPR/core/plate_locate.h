//////////////////////////////////////////////////////////////////////////
// Name:	    plate_locate Header
// Version:		1.2
// Date:	    2014-09-19
// MDate:		2014-09-29
// MDate:	    2015-03-13
// Author:	    liuruoze
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:
// Defines CPlateLocate
//////////////////////////////////////////////////////////////////////////
#ifndef EASYPR_CORE_PLATELOCATE_H_
#define EASYPR_CORE_PLATELOCATE_H_

#include "core/plate.hpp"
#include "basedef.h"
/*! \namespace easypr
	Namespace where all the C++ EasyPR functionality resides
*/

using namespace std;

namespace easypr
{

	class EASYPR_API CPlateLocate
	{
	public:
		// ���캯��
		CPlateLocate();

		// ���ò���
		void setLifemode(bool param);

		// ��ȡ/���ø���������ֵ
		inline void setGaussianBlurSize(int param) { m_GaussianBlurSize = param; }
		inline int getGaussianBlurSize() const { return m_GaussianBlurSize; }

		inline void setMorphSizeWidth(int param) { m_MorphSizeWidth = param; }
		inline int getMorphSizeWidth() const { return m_MorphSizeWidth; }

		inline void setMorphSizeHeight(int param) { m_MorphSizeHeight = param; }
		inline int getMorphSizeHeight() const { return m_MorphSizeHeight; }

		inline void setVerifyError(float param) { m_error = param; }
		inline float getVerifyError() const { return m_error; }

		inline void setVerifyAspect(float param) { m_aspect = param; }
		inline float getVerifyAspect() const { return m_aspect; }

		inline void setVerifyMin(int param) { m_verifyMin = param; }
		inline void setVerifyMax(int param) { m_verifyMax = param; }

		inline void setJudgeAngle(int param) { m_angle = param; }

		inline void setDebug(bool param) { m_debug = param; }
		inline bool getDebug() { return m_debug; }

		// ��ɫ��λ��������
		int plateColorLocate(Mat src, std::vector<CPlate>& candPlates, int index = 0);
		// Sobel��λ��������
		int plateSobelLocate(Mat src, std::vector<CPlate>& candPlates, int index = 0);
		// Mser���ֶ�λ��������
		int plateMserLocate(Mat src, std::vector<CPlate>& candPlates, int index = 0);
		// �ۺϳ�������λ
		int plateLocate(Mat, std::vector<Mat>&, int = 0);
		// �ۺϳ�������λ
		int plateLocate(Mat, std::vector<CPlate>&, int = 0);

	private:
		// ȥ�롢Sobel��Ե��ȡ����̬ѧ����
		int _sobelOper(const Mat& in, Mat& out, int blurSize, int morphW, int morphH);
		// ȥ�롢Sobel��Ե��ȡ����̬ѧ����
		int _sobelOperT(const Mat& in, Mat& out, int blurSize, int morphW, int morphH);
		// �ߴ��жϣ����ݳ�������Ϳ�߱������гߴ��жϣ�
		bool _verifySizes(RotatedRect mr);

		// ��Դͼ�����������γ�������
		int _sobelFrtSearch(const Mat& src, std::vector<Rect_<float>>& outRects);
		// �ڵõ��ľ���ͼ���ж���������������refpoint��boundͼ����ԭͼ�������ϽǶ��������
		int _sobelSecSearch(Mat& bound, Point2f refpoint,
			std::vector<RotatedRect>& outRects);
		// �ھ��ο����ٴν��������������Ǿ��������ľ��ο�
		int _sobelSecSearchPart(Mat& bound, Point2f refpoint,
			std::vector<RotatedRect>& outRects);

		// ͨ����ɫ��������λ���γ�������
		int _colorSearch(const Mat& src, const Color r, Mat& out,
			std::vector<RotatedRect>& outRects);
		// ͨ�����ֶ�λ��ȷ�����γ�������
		int _mserSearch(const Mat &src, vector<Mat>& out,
			vector<vector<CPlate>>& out_plateVec, bool usePlateMser, vector<vector<RotatedRect>>& out_plateRRect,
			int img_index = 0, bool showDebug = false);

		// ��ͼ�ο�����󣬽�����ת
		bool _rotation(Mat& in, Mat& out, const Size rect_size, const Point2f center,
			const double angle);
		// ����б�ʣ��жϳ����Ƿ�ƫб�ˣ�slope��б��
		bool _isdeflection(const Mat& in, const double angle, double& slope);
		// ����任��Ť������
		void _affine(const Mat& in, Mat& out, const double slope);
		// ɾ����Ч���򣬱��������� ���ұ߽���Ч����
		void _deleteNotArea(Mat &inmat, Color color = UNKNOWN);
		// ��Ťб����
		int _deskew(const Mat& src, const Mat& src_b, std::vector<RotatedRect>& inRects, std::vector<CPlate>& outPlates,
			bool useDeteleArea = true, Color color = UNKNOWN);

	protected:
		int		m_GaussianBlurSize;		// ��˹ģ��Ԫ�ش�С
		int		m_MorphSizeWidth;		// ��̬ѧ������ģ���
		int		m_MorphSizeHeight;		// ��̬ѧ������ģ���

		float	m_error;				// ��߱�ƫ����
		float	m_aspect;				// һ�㳵�ƵĿ�߱�
		int		m_verifyMin;			// ��С���ϵ��
		int		m_verifyMax;			// ������ϵ��
		int		m_angle;				// ���ڳ����жϵ���б�Ƕ�

		bool	m_debug;				// �Ƿ������ԣ���ͼ����ʾ���洢��		
	};

} /*! \namespace easypr*/

#endif  // EASYPR_CORE_PLATELOCATE_H_