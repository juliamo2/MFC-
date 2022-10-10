#ifndef __IJZ_UIENGINE_H__
#define __IJZ_UIENGINE_H__
#include <JZCommonImageDef.h>
#include <Windows.h>

class IJZUIEngine
{
public:
	// ��ʼ��UIEngine�г�Ա
	virtual JZ_RESULT Init(HWND hWnd) = 0;
	// �ͷ�UIEngine�г�Ա
	virtual JZ_RESULT Release() = 0;
	// ����Ҫ�����ͼ������
	virtual JZ_RESULT SetImageData(const char* filename) = 0;
	// �Ƿ��Ѿ�������Ҫ�����ͼ��
	virtual bool IsSetSrcImage() = 0;
	// ��������ͼ�����ݱ���ΪͼƬ
	virtual JZ_RESULT SaveImageData(const char* filename) = 0;
	// ����ͼ����Ĳ���
	virtual JZ_RESULT SetProcessParam(JZCommonParam* param) = 0;
	// ����ͼ�������ͽ���ͼ����
	virtual JZ_RESULT ProcessImage(JZ_IMAGEPROC_TYPE processType, JZ_BASEPROCESS_TYPE baseProcessType = JZ_BASEPROCESS_UNKNOWN) = 0;
	// ��ȡ�洢�Ķ���ͼ����������
	virtual JZImageProcessExtraData* GetExtraData() = 0;
	// ��Ⱦ����
	virtual JZ_RESULT Render() = 0;

};

typedef JZ_RESULT(*DefGetUIEngineInterface)(IJZUIEngine** ppAPI);
typedef JZ_RESULT(*DefReleaseUIEngineInterface)(IJZUIEngine*& pAPI);

typedef struct tag_JZUIEngineAPI
{
	DefGetUIEngineInterface pfnGetInterface;
	DefReleaseUIEngineInterface pfnReleaseInterface;
}JZUIEngineAPI;
#endif // __IJZ_UIENGINE_H__

