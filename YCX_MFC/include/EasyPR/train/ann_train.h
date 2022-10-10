#ifndef EASYPR_TRAIN_ANNTRAIN_H_
#define EASYPR_TRAIN_ANNTRAIN_H_

#include "train/train.h"
#include "util/kv.h"
#include <memory>
#include "basedef.h"
namespace easypr
{
	class EASYPR_API AnnTrain : public ITrain
	{
	public:
		// ���캯��
		explicit AnnTrain(const char* chars_folder, const char* xml);
		// ѵ���õ�annģ��
		virtual void train();
		// ���Եõ���annģ��
		virtual void test();

	private:
		// �����������������ݺ�������������ݣ����õ�TrainData��������������ѵ��
		virtual cv::Ptr<cv::ml::TrainData> _tdata();
		// �Ը����ַ�ͼ����м��α任(ƽ��/��ת)���Ӷ��˹��ϳɵõ��µ�ͼ������ѵ��
		cv::Mat _getSyntheticImage(const cv::Mat& image);
		// �����������������ݺ�������������ݣ����õ�TrainData��������������ѵ����number_for_count��ʾÿ���ַ�����Ҫ���ٸ�ͼ��������㣬�������֮ǰ��ͼ�����
		cv::Ptr<cv::ml::TrainData> _sdata(size_t number_for_count = 100);
		// ʶ������������ַ�ͼƬ(�������������ַ�ͼƬ)
		std::pair<std::string, std::string> _identifyChinese(cv::Mat input);
		// ʶ��������ַ�ͼƬ(���������ġ���ĸ������)
		std::pair<std::string, std::string> _identify(cv::Mat input);


	private:
		cv::Ptr<cv::ml::ANN_MLP>	m_ann;				// ANN_MLP�����ָ�룬����ѵ���Ͳ���annģ��
		const char*					m_ann_xml;			// ���ڴ��ѵ���õ���ģ��
		const char*					m_chars_folder;		// ����˺ܶ��ѵ���ľ���ͼ����ļ���·��
		std::shared_ptr<Kv>			m_kv;
		int							m_type;				// 0-��ʾѵ�������ַ������ֺ���ĸ��65���ַ���1-��ʾѵ�������ַ�
	};
}

#endif  // EASYPR_TRAIN_ANNTRAIN_H_