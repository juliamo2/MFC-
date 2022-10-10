#ifndef EASYPR_CORE_PLATEJUDGE_H_
#define EASYPR_CORE_PLATEJUDGE_H_

#include "core/plate.hpp"
#include "core/feature.h"
#include "basedef.h"
namespace easypr
{

	class EASYPR_API PlateJudge
	{
	public:
		// ���캯��
		PlateJudge();
		// ��ȡ��������
		static PlateJudge* instance();
		// ����xml�ļ�·������ȡSVMģ��
		void LoadModel(std::string path);
		// ��SVMģ�͵÷ֵĻ����ϣ����ϷǼ���ֵ���ƣ�NMS�����ж��Ƿ�Ϊ����
		int plateJudgeUsingNMS(const std::vector<CPlate>&, std::vector<CPlate>&, int maxPlates = 5);
		// ����SVMģ���ж��Ƿ�Ϊ����
		int plateJudge(const Mat& plateMat);
		// ����SVMģ���ж��Ƿ�Ϊ����
		int plateJudge(const std::vector<Mat> &inVec,
			std::vector<Mat> &resultVec);
		// ����SVMģ���ж��Ƿ�Ϊ����
		int plateJudge(const std::vector<CPlate> &inVec,
			std::vector<CPlate> &resultVec);

	private:
		// ����SVMģ�ͣ�Ԥ������ǳ��Ƶĵ÷֣��ж��Ƿ�Ϊ���ƣ�0 is plate, -1 is not.
		int _plateSetScore(CPlate& plate);
		// �Ǽ���ֵ����
		void _NMS(std::vector<CPlate> &inVec, std::vector<CPlate> &resultVec, double overlap);
	private:
		cv::Ptr<ml::SVM> m_pSvm;			// SVM����ָ��
		static PlateJudge* m_pInstance;		// ��������
		svmCallback pfnExtractFeature;		// ������ȡ�Ļص��ӿ�



	};
}

#endif  // EASYPR_CORE_PLATEJUDGE_H_