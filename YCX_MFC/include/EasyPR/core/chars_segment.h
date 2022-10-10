#ifndef EASYPR_CORE_CHARSSEGMENT_H_
#define EASYPR_CORE_CHARSSEGMENT_H_

#include "opencv2/opencv.hpp"
#include "config.h"
#include "basedef.h"
using namespace cv;
using namespace std;

namespace easypr
{

	class EASYPR_API CCharsSegment
	{
	public:
		// ���캯��
		CCharsSegment();
		// �ָ��ַ�
		int charsSegment(Mat input, std::vector<Mat>& resultVec, Color color = BLUE);
		//! using methods to segment chars in plate
		int charsSegmentUsingOSTU(Mat input, std::vector<Mat>& resultVec, std::vector<Mat>& grayChars, Color color = BLUE);
		int charsSegmentUsingMSER(Mat input, vector<Mat>& resultVec, vector<Mat>& grayChars, Color color = BLUE);
		//! using project 
		int projectSegment(const Mat& input, Color color, vector<int>& out_indexs);

		// ��������/��ȡ����
		inline void setLiuDingSize(int param) { m_LiuDingSize = param; }
		inline void setColorThreshold(int param) { m_ColorThreshold = param; }

		inline void setBluePercent(float param) { m_BluePercent = param; }
		inline float getBluePercent() const { return m_BluePercent; }

		inline void setWhitePercent(float param) { m_WhitePercent = param; }
		inline float getWhitePercent() const { return m_WhitePercent; }

		inline void setDebug(int param) { m_debug = param; }
		inline int getDebug() { return m_debug; }

	private:
		// �ж��ַ����Ƿ�����ߴ��С
		bool _verifyCharSizes(Mat r);
		// �ж��ַ����γߴ��С
		bool _verifyCharRectSizes(Rect r);
		// find the best chinese binaranzation method�������ַ���ֵ��ֵ��
		void _judgeChinese(Mat in, Mat& out, Color plateType);
		void _judgeChineseGray(Mat in, Mat& out, Color plateType);
		// �������������ַ���ֵ��ֵ��
		bool _slideChineseWindow(Mat& image, Rect mr, Mat& newRoi, Color plateType, float slideLengthRatio, bool useAdapThreshold);
		bool _slideChineseGrayWindow(const Mat& image, Rect& mr, Mat& newRoi, Color plateType, float slideLengthRatio);
		// ���ַ�����Ϊָ����С20*20
		Mat _preprocessChar(Mat in);
		// ͨ�������ַ���λ�ã�Ѱ�������ַ���
		Rect _GetChineseRect(const Rect rectSpe);
		// Ѱ�������ַ���(��ƺ����Ӣ���ַ�)
		int _GetSpecificRect(const std::vector<Rect>& vecRect);
		// �Ƴ������ַ���ߵľ��ο飬�ӳ����ַ��ұ߿�ʼ��ѡ��6�����ο�(���������ַ�)
		int _RebuildRect(const std::vector<Rect>& vecRect, std::vector<Rect>& outRect,
			int specIndex);
		int _getNearestIndex(Point center, const vector<Point>& groundCenters);

	private:
		int		m_LiuDingSize;			// ������С��Ĭ��Ϊ7
		int		m_theMatWidth;			// ���ƿ�ȣ�Ĭ��Ϊ136
		int		m_ColorThreshold;		// ��ɫ��ֵ��Ĭ��Ϊ150
		float	m_BluePercent;			// ��ɫ�ٷֱȣ�Ĭ��Ϊ30%
		float	m_WhitePercent;			// ��ɫ�ٷֱȣ�Ĭ��Ϊ10%
		int		m_debug;				// �Ƿ���е��ԣ���ʾ�м�ͼ��
	};

}

#endif  // EASYPR_CORE_CHARSSEGMENT_H_