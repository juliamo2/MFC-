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
	// ����OpenGL�豸
	virtual JZ_RESULT SetDevice(HWND hWnd) = 0;
	// ����shader��Դ
	virtual void SetShader() = 0;
	// ����Ҫ��Ⱦ�����ͼ�� ��֧��RGB
	virtual void SetLeftImage(JZImageBuf* pImageBuf = NULL) = 0;
	// ����Ҫ��Ⱦ���Ҳ�ͼ�� ��֧��RGB
	virtual void SetRightImage(JZImageBuf* pImageBuf = NULL) = 0;
	// ���ñ�����ɫ
	virtual void SetGroundColor(glm::vec4 color = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f)) = 0;
	// ��ʼ����Ⱦ��Ҫ�Ļ�������
	virtual void init(HWND hWnd) = 0;
	// ��Ⱦ����ͼ��
	virtual void RenderScene() = 0;
	// �ͷ��ڴ�
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

