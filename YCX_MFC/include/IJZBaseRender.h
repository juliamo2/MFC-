#ifndef __IJZ_BASERENDER_H__
#define __IJZ_BASERENDER_H__
#include <JZCommonImageDef.h>
#include <vector>
#include <glm/glm.hpp>

class IJZBaseRender
{
public:
	IJZBaseRender() {}
	~IJZBaseRender() {}
};

//
class IJZSceneRender: public IJZBaseRender
{
public:
	// 设置OpenGL设备
	virtual JZ_RESULT SetDevice(HWND hWnd) = 0;
	// 设置shader资源
	virtual void SetShader() = 0;
	// 设置要渲染的左侧图像， 仅支持RGB
	virtual void SetLeftImage(JZImageBuf* pImageBuf = NULL) = 0;
	// 设置要渲染的右侧图像， 仅支持RGB
	virtual void SetRightImage(JZImageBuf* pImageBuf = NULL) = 0;
	// 设置背景颜色
	virtual void SetGroundColor(glm::vec4 color = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f)) = 0;
	// 初始化渲染需要的基本数据
	virtual void init(HWND hWnd) = 0;
	// 渲染绘制图形
	virtual void RenderScene() = 0;
	// 释放内存
	virtual void Release() = 0;
};

typedef JZ_RESULT(*DefGetSceneInterface)(IJZSceneRender** ppScene);
typedef JZ_RESULT(*DefReleaseSceneInterface)(IJZSceneRender*& pScene);

typedef struct tag_JZBaseRenderAPI
{
	DefGetSceneInterface pfnGetSceneInterface;
	DefReleaseSceneInterface pfnReleaseSceneInterface;
}JZBaseRenderAPI;

#endif // !__IJZ_BASERENDER_H__

