#ifndef EASYPR_CORE_CHARSIDENTIFY_H_
#define EASYPR_CORE_CHARSIDENTIFY_H_

#include <memory>
#include "opencv2/opencv.hpp"

#include "util/kv.h"
#include "core/character.hpp"
#include "core/feature.h"
#include "basedef.h"
namespace easypr
{

	 class EASYPR_API CharsIdentify
	{
	public:
		// ���캯��
		CharsIdentify();
		// ��ȡ������ʵ��ָ��
		static CharsIdentify* instance();
		// ��ȡģ��
		void LoadModel(std::string path);
		void LoadChineseModel(std::string path);
		void LoadGrayChANN(std::string path);
		void LoadChineseMapping(std::string path);
		// �ַ�����
		int classify(cv::Mat f, float& maxVal, bool isChinses = false, bool isAlphabet = false);
		void classify(cv::Mat featureRows, std::vector<int>& out_maxIndexs, std::vector<float>& out_maxVals, std::vector<bool> isChineseVec);
		void classify(std::vector<CCharacter>& charVec);
		void classifyChinese(std::vector<CCharacter>& charVec);
		void classifyChineseGray(std::vector<CCharacter>& charVec);
		// �ַ�������
		std::pair<std::string, std::string> identify(cv::Mat input, bool isChinese = false, bool isAlphabet = false);
		int identify(std::vector<cv::Mat> inputs, std::vector<std::pair<std::string, std::string>>& outputs, std::vector<bool> isChineseVec);
		std::pair<std::string, std::string> identifyChinese(cv::Mat input, float& result, bool& isChinese);
		std::pair<std::string, std::string> identifyChineseGray(cv::Mat input, float& result, bool& isChinese);

		bool isCharacter(cv::Mat input, std::string& label, float& maxVal, bool isChinese = false);

	private:
		annCallback					pfnExtractFeature;			// ������ȡ�ص��ӿ�
		static CharsIdentify*		m_pInstance;				// ������ʵ��ָ��
		cv::Ptr<cv::ml::ANN_MLP>	m_ann;						// �ַ�����annģ��
		cv::Ptr<cv::ml::ANN_MLP>	m_annChinese;				// �����ַ�����annģ��
		cv::Ptr<cv::ml::ANN_MLP>	m_annGray;					// �Ҷ������ַ�����annģ��
		std::shared_ptr<Kv>			m_kv;						// ����ӳ����
	};
}

#endif  //  EASYPR_CORE_CHARSIDENTIFY_H_