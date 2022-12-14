#ifndef __IJZ_UIENGINE_H__
#define __IJZ_UIENGINE_H__
#include <JZCommonImageDef.h>
#include <Windows.h>

class IJZUIEngine
{
public:
	// 初始化UIEngine中成员
	virtual JZ_RESULT Init(HWND hWnd) = 0;
	// 释放UIEngine中成员
	virtual JZ_RESULT Release() = 0;
	// 设置要处理的图像数据
	virtual JZ_RESULT SetImageData(const char* filename) = 0;
	// 是否已经设置了要处理的图像
	virtual bool IsSetSrcImage() = 0;
	// 将处理后的图像数据保存为图片
	virtual JZ_RESULT SaveImageData(const char* filename) = 0;
	// 设置图像处理的参数
	virtual JZ_RESULT SetProcessParam(JZCommonParam* param) = 0;
	// 根据图像处理类型进行图像处理
	virtual JZ_RESULT ProcessImage(JZ_IMAGEPROC_TYPE processType, JZ_BASEPROCESS_TYPE baseProcessType = JZ_BASEPROCESS_UNKNOWN) = 0;
	// 获取存储的额外图像处理结果数据
	virtual JZImageProcessExtraData* GetExtraData() = 0;
	// 渲染场景
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

