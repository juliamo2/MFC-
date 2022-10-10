#ifndef EASYPR_TRAIN_SVMTRAIN_H_
#define EASYPR_TRAIN_SVMTRAIN_H_

#include "train/train.h"
#include <vector>
#include "config.h"
#include "core/feature.h"
#include "basedef.h"
namespace easypr
{
	class EASYPR_API SvmTrain : public ITrain
	{
	public:
		typedef struct
		{
			std::string file;	// ͼƬ�ļ���(������չ��)
			SvmLabel label;		// ͼƬ��ǩ����Ϊ�г��ƺ�û��������
		} TrainItem;

		// ���캯��
		SvmTrain(const char* plates_folder, const char* xml);
		// ѵ���õ�svmģ��
		virtual void train();
		// ���Եõ���svmģ��
		virtual void test();

	private:
		// �����ļ���·�����õ�ͼƬ��׼��ѵ���Ͳ�������
		void _prepare();
		// ����ѵ��ͼƬ������svmѵ������
		virtual cv::Ptr<cv::ml::TrainData> _tdata();

	private:
		cv::Ptr<cv::ml::SVM>	m_pSvm;					// SVM�����ָ�룬����ѵ���Ͳ���svmģ��
		const char*				m_plates_folder;		// ����˺ܶ��ѵ���ľ���ͼ����ļ���·��
		const char*				m_svm_xml;				// ���ڴ��ѵ���õ���ģ��
		std::vector<TrainItem>	m_train_file_list;		// ��ѵ����ͼƬ��Ŀ����
		std::vector<TrainItem>	m_test_file_list;		// �����Ե�ͼƬ��Ŀ����
		svmCallback				pfnExtractFeature;		// ������ȡ�Ļص��ӿ�
		bool					m_isPrepared = true;	// �Ƿ��Ѿ�׼������ѵ������
	};
}

#endif  // EASYPR_TRAIN_SVMTRAIN_H_
