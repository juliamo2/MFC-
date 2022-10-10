#ifndef __IJZ_RUNTIMEOGL_H__
#define __IJZ_RUNTIMEOGL_H__
#include <JZCommonImageDef.h>
#include <JZCommonRenderDef.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class IJZDevice;
class IJZTexture;
class IJZShader;
class IJZMesh;
enum JZ_RES_TYPE
{
	JZ_RES_UNKNOW,
	JZ_RES_DEVICE,			// OpenGL�豸��Դ
	JZ_RES_SHADER,			// OpenGL shader��Դ
	JZ_RES_TEX,				// OpenGL ������Դ
	JZ_RES_MESH,			// OpenGL������Դ
};

typedef struct tag_Vertex
{
	glm::vec3 position;		// ��������
	glm::vec3 color;		// ������ɫ
	glm::vec2 texture;		// ������������
}Vertex;

// ��Դ����
class IJZBaseRes
{
public:
	// ��ȡ��Դ����
	virtual JZ_RES_TYPE GetResType() = 0;
};

// OpenGL�豸��Դ
class IJZDevice : public IJZBaseRes
{
public:
	// ��ȡ��Դ����
	virtual JZ_RES_TYPE GetResType() = 0;
	// ��ʼ��OpenGL��Ⱦ����
	virtual JZ_RESULT Init(HWND hWnd, HDC hDC = NULL, HGLRC hShareRC = NULL) = 0;
	// �ͷ��豸��Դ
	virtual JZ_RESULT Release() = 0;
	// ʹ��(��)�豸
	virtual JZ_RESULT Bind() = 0;
	// �����
	virtual JZ_RESULT UnBind() = 0;
	// ��������Ϊ����ͼƬ
	virtual JZ_RESULT DumpTex(IJZTexture* pTex, const char* filepath) = 0;
	// �ڸ��豸����ʾ������
	virtual JZ_RESULT Display(IJZTexture* pTexture) = 0;
	// ��ȡOpenGL��Ⱦ�������
	virtual HGLRC GetHGLRC() = 0;
	// ������ȾĿ��
	virtual JZ_RESULT SetRenderTarget(IJZTexture* pTargetTex, bool bClear = true, glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 0.0)) = 0;
	virtual JZ_RESULT SetRenderTarget(unsigned int* pFBO, IJZTexture* pTargetTex) = 0;
	virtual JZ_RESULT SetRenderTarget(IJZTexture* pTargetTex, IJZTexture* pDepthTex, bool bClear = true, glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 0.0),
		float depth = 1.0, int stencil = 0) = 0;
	virtual JZ_RESULT SetRenderTarget(IJZTexture** ppTargetTex, unsigned int nNumRTs, glm::vec4 dwColor, bool bClear) = 0;
	// �����Ⱦ����Ϊָ��ֵ
	virtual JZ_RESULT ClearRenderTarget(glm::vec4 dwColor) = 0;
	virtual JZ_RESULT ClearRenderTarget(IJZTexture** ppTargetTex, unsigned int nNumRTs, glm::vec4 dwColor) = 0;
	virtual JZ_RESULT ClearRenderTarget(bool bClearColor, glm::vec4 dwColor, bool bClearDepth, float depth, bool bClearStencil, int stencil) = 0;
	virtual JZ_RESULT ClearRenderTarget(glm::vec4 dwColor, float depth, int stencil) = 0;
	// ������ģ�建��Ϊָ��ֵ
	virtual JZ_RESULT ClearDepthStencil(float Depth = 1.0f, UINT8 Stencil = 0) = 0;
	// �����ӿ�
	virtual JZ_RESULT SetViewPort(JZViewPort* pViewPort) = 0;
	// ��ȡ��ǰ�ӿ�
	virtual JZ_RESULT GetViewPort(JZViewPort* pViewPort) = 0;
	// ����alpha���״̬
	virtual JZ_RESULT SetAlphaBlendStatus(JZAlphaBlendDesc* pAlphaBlend) = 0;
	// �������ģ�����״̬
	virtual JZ_RESULT SetDepthStencilStatus(JZDepthStencilDesc* pDepthStencil) = 0;
	// �������޳�״̬
	virtual JZ_RESULT SetRasterizerStatus(JZRasterizerDesc* pRasterDesc) = 0;
};

// OpenGL��shader��Դ
class IJZShader : public IJZBaseRes
{
public:
	// ��ȡ��Դ����
	virtual JZ_RES_TYPE GetResType() = 0;
	// ʹ����ɫ������
	virtual void Use() = 0;
	// ���ʹ����ɫ������
	virtual void UnUse() = 0;
	// shaderName��ʾ������shader·�����ַ������飬iShaderNums��ʾ���ַ�����������˼���shader·�����ַ�������Ӧ�ð��ն�����ɫ����Ƭ����ɫ����������ɫ����˳������
	virtual JZ_RESULT Create(const char** shaderName, int iShaderNums) = 0;
	virtual JZ_RESULT Create(JZShaderInfo* shaders, int iShaderNums) = 0;
	// ��ȡ��ɫ������ID
	virtual unsigned int GetProgramID() = 0;
	// �ͷ���ɫ������
	virtual void Release() = 0;
	// ��ȡshader��uniform������λ��
	virtual unsigned int GetParamLoc(IN const char* paramName, IN OUT unsigned int* pParamLoc = NULL) = 0;
	// ��ȡshader���Ӻ���������
	virtual unsigned int GetSubroutineIndex(IN const char* subroutineName, IN JZ_SHADER_TYPE shaderType, IN OUT unsigned int* pSubIndex) = 0;
	// ����shader��Ҫ���õ��Ӻ�������
	virtual bool SetSubroutineIndex(IN unsigned int subIndex, IN JZ_SHADER_TYPE shaderType) = 0;
	// ����shader��unform������ֵ
	virtual bool SetInt(IN unsigned int locInt, IN int nVal) = 0;
	virtual bool SetIntArray(IN unsigned int locIntArray, IN const int* piValue, IN int iDim) = 0;
	virtual bool SetFloat(IN unsigned int locFloat, IN float fVal) = 0;
	virtual bool SetFloatArray(IN unsigned int locFloatArray, IN const float *pf, IN unsigned int num) = 0;
	virtual bool SetVector(IN unsigned int locVector, IN const float* pv4) = 0;
	virtual bool SetVectorArray(IN unsigned int locVectorArray, IN const float* pVector, IN unsigned int num) = 0;
	virtual bool SetMatrix(IN unsigned int locMatrix, IN const float* pMatrix) = 0;
	virtual bool SetMatrixArray(IN unsigned int locMatrixArray, IN const float* pMatrix, IN unsigned int num) = 0;
	virtual bool SetTexture(IN unsigned int locTexture, IN unsigned int texID, IN JZTexSampDesc* pSamplerDesc = NULL) = 0;
};

// OpenGL������Դ
class IJZTexture : public IJZBaseRes
{
public:
	// ��ȡ��Դ����
	virtual JZ_RES_TYPE GetResType() = 0;
	// ����������Դ��Ŀǰ��֧��RGBͼ��
	virtual JZ_RESULT Create(JZTextureDesc* pTexDesc) = 0;
	// �ͷ�������Դ
	virtual JZ_RESULT Release() = 0;
	// �����������ͼ�����ݣ�Ŀǰֻ֧�ֺ��Ѿ�������������һ����������ýӿ�����
	virtual JZ_RESULT FillImage(JZImageBuf* pImageBuf) = 0;
	// ������д�뵽ͼƬ�ļ�����֧��bmpͼ���ʽ
	//virtual bool Dump(const char* filepath) = 0;
	// ��ȡ������ID
	virtual unsigned int GetTexID() = 0;
	// ��ȡ�������ID
	virtual unsigned int GetTexDepthID() = 0;
	// ��ȡ������
	virtual int GetTexWidth() = 0;
	// ��ȡ����߶�
	virtual int GetTexHeight() = 0;
};

// OpenGL������Դ
class IJZMesh : public IJZBaseRes
{
public:
	// ��ȡ��Դ����
	virtual JZ_RES_TYPE GetResType() = 0;
	// ������������������������Դ
	virtual JZ_RESULT CreateMesh(JZMeshDesc* pMeshDesc) = 0;
	// ����������ʾͼ���������Դ
	virtual JZ_RESULT CreateQuadMesh() = 0;
	// ���ݻ�������Ŀ�߱Ⱥ������߱ȴ���������Դ
	virtual JZ_RESULT CreateQuadMesh(float rectAspect, float texAspect) = 0;
	// �ͷ�������Դ
	virtual JZ_RESULT Release() = 0;
	// ��������
	//virtual JZ_RESULT Draw() = 0;
	// ��������
	virtual JZ_RESULT Draw(UINT uStartIndexLocation = 0, UINT uIndexCount = 0) = 0;
};

// OpenGL�����ϵͳ
class IJZCamera
{
public:
	// �������λ��
	virtual void SetCameraPos(glm::vec3 position) = 0;
	// ��������ǶȲ���Ϊ-1ʱ����ʾ����ԭ��������
	virtual void SetCameraAngle(float pitch = -1, float yaw = -1, float roll = -1) = 0;
	// �����������
	virtual void SetCameraVec(glm::vec3 front) = 0;
	// ��ȡ��ͼ����
	virtual glm::mat4 GetViewMatrix() = 0;
};

typedef JZ_RESULT(*DefCreateOGLDevice)(IJZDevice** ppDevice);
typedef JZ_RESULT(*DefReleaseOGLDevice)(IJZDevice*& pDevice);
typedef JZ_RESULT(*DefCreateOGLShader)(IJZShader** ppShader);
typedef JZ_RESULT(*DefReleaseOGLShader)(IJZShader*& pShader);
typedef JZ_RESULT(*DefCreateOGLMesh)(IJZMesh** ppMesh);
typedef JZ_RESULT(*DefReleaseOGLMesh)(IJZMesh*& pMesh);
typedef JZ_RESULT(*DefCreateOGLTexture)(IJZTexture** ppTexture);
typedef JZ_RESULT(*DefReleaseOGLTexture)(IJZTexture*& pTexture);
typedef JZ_RESULT(*DefCreateOGLCamera)(IJZCamera** ppCamera);
typedef JZ_RESULT(*DefReleaseOGLCamera)(IJZCamera*& pCamera);

typedef struct tag_JZRuntimeOGLAPI
{
	DefCreateOGLDevice		pfnCreateOGLDevice;
	DefReleaseOGLDevice		pfnReleaseOGLDevice;
	DefCreateOGLShader		pfnCreateOGLShader;
	DefReleaseOGLShader		pfnReleaseOGLShader;
	DefCreateOGLMesh		pfnCreateOGLMesh;
	DefReleaseOGLMesh		pfnReleaseOGLMesh;
	DefCreateOGLTexture		pfnCreateOGLTexture;
	DefReleaseOGLTexture	pfnReleaseOGLTexture;
	DefCreateOGLCamera		pfnCreateOGLCamera;
	DefReleaseOGLCamera		pfnReleaseOGLCamera;
}JZRuntimeOGLAPI;

#endif // !__IJZ_RUNTIMEOGL_H__