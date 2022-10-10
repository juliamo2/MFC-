#ifndef EASYPR_TRAIN_ANNCHTRAIN_H_
#define EASYPR_TRAIN_ANNCHTRAIN_H_

#include "train/train.h"
#include "util/kv.h"
#include "core/feature.h"
#include <memory>
#include "basedef.h"
namespace easypr
{

	class EASYPR_API AnnChTrain : public ITrain
	{
	public:
		// ���캯��
		explicit AnnChTrain(const char* chars_folder, const char* xml);
		// ��ԭʼ���ݻ��ߣ�ԭʼ����+�ϳ����ݣ�����ѵ���õ�annģ��
		void trainVal(size_t number_for_count = 100);
		// ѵ���õ�annģ��
		virtual void train();
		// ���Եõ���annģ��
		virtual void test();
		// ������Ҫ���ַ�ͼ��ĸ���
		inline void setNumberForCount(int n) { m_number_for_count = n; }

	private:
		// �����������������ݺ�������������ݣ����õ�TrainData��������������ѵ��
		virtual cv::Ptr<cv::ml::TrainData> _tdata();
		// ʶ��Ҷ������ַ�ͼ��
		std::pair<std::string, std::string> _identifyGrayChinese(cv::Mat input);


	private:
		cv::Ptr<cv::ml::ANN_MLP>	m_ann;					// ANN_MLP�����ָ�룬����ѵ���Ͳ���annģ��
		const char*					m_ann_xml;				// ���ڴ��ѵ���õ���ģ��
		const char*					m_chars_folder;			// ����˺ܶ��ѵ���ľ���ͼ����ļ���·��

		std::shared_ptr<Kv>			m_kv;
		int							m_type;					// 0-��ʾѵ�������ַ������ֺ���ĸ��65���ַ���1-��ʾѵ�������ַ�
		int							m_number_for_count;		// ��ʾÿ���ַ�����Ҫ���ٸ�ͼ��������㣬�������֮ǰ��ͼ�����
		annCallback					pfnExtractFeature;		// ������ȡ�Ļص��ӿ�
	};
}

#endif  // EASYPR_TRAIN_ANNCHTRAIN_H_