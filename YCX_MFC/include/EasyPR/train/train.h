#ifndef EASYPR_TRAIN_TRAIN_H_
#define EASYPR_TRAIN_TRAIN_H_

#include <opencv2/opencv.hpp>

namespace easypr
{
	class ITrain
	{
	public:
		ITrain();

		virtual ~ITrain();
		// ѵ���õ�ģ��
		virtual void train() = 0;
		// ���Եõ���ģ��
		virtual void test() = 0;

	private:
		// ����ѵ��ͼƬ������ѵ������
		virtual cv::Ptr<cv::ml::TrainData> _tdata() = 0;
	};
}

#endif  // EASYPR_TRAIN_TRAIN_H_