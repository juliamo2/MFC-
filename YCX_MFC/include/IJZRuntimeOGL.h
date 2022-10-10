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
	JZ_RES_DEVICE,			// OpenGL设备资源
	JZ_RES_SHADER,			// OpenGL shader资源
	JZ_RES_TEX,				// OpenGL 纹理资源
	JZ_RES_MESH,			// OpenGL网格资源
};

typedef struct tag_Vertex
{
	glm::vec3 position;		// 顶点坐标
	glm::vec3 color;		// 顶点颜色
	glm::vec2 texture;		// 顶点纹理坐标
}Vertex;

// 资源基类
class IJZBaseRes
{
public:
	// 获取资源类型
	virtual JZ_RES_TYPE GetResType() = 0;
};

// OpenGL设备资源
class IJZDevice : public IJZBaseRes
{
public:
	// 获取资源类型
	virtual JZ_RES_TYPE GetResType() = 0;
	// 初始化OpenGL渲染环境
	virtual JZ_RESULT Init(HWND hWnd, HDC hDC = NULL, HGLRC hShareRC = NULL) = 0;
	// 释放设备资源
	virtual JZ_RESULT Release() = 0;
	// 使用(绑定)设备
	virtual JZ_RESULT Bind() = 0;
	// 解除绑定
	virtual JZ_RESULT UnBind() = 0;
	// 将纹理导出为本地图片
	virtual JZ_RESULT DumpTex(IJZTexture* pTex, const char* filepath) = 0;
	// 在该设备上显示纹理画面
	virtual JZ_RESULT Display(IJZTexture* pTexture) = 0;
	// 获取OpenGL渲染环境句柄
	virtual HGLRC GetHGLRC() = 0;
	// 设置渲染目标
	virtual JZ_RESULT SetRenderTarget(IJZTexture* pTargetTex, bool bClear = true, glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 0.0)) = 0;
	virtual JZ_RESULT SetRenderTarget(unsigned int* pFBO, IJZTexture* pTargetTex) = 0;
	virtual JZ_RESULT SetRenderTarget(IJZTexture* pTargetTex, IJZTexture* pDepthTex, bool bClear = true, glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 0.0),
		float depth = 1.0, int stencil = 0) = 0;
	virtual JZ_RESULT SetRenderTarget(IJZTexture** ppTargetTex, unsigned int nNumRTs, glm::vec4 dwColor, bool bClear) = 0;
	// 清除渲染缓存为指定值
	virtual JZ_RESULT ClearRenderTarget(glm::vec4 dwColor) = 0;
	virtual JZ_RESULT ClearRenderTarget(IJZTexture** ppTargetTex, unsigned int nNumRTs, glm::vec4 dwColor) = 0;
	virtual JZ_RESULT ClearRenderTarget(bool bClearColor, glm::vec4 dwColor, bool bClearDepth, float depth, bool bClearStencil, int stencil) = 0;
	virtual JZ_RESULT ClearRenderTarget(glm::vec4 dwColor, float depth, int stencil) = 0;
	// 清除深度模板缓存为指定值
	virtual JZ_RESULT ClearDepthStencil(float Depth = 1.0f, UINT8 Stencil = 0) = 0;
	// 设置视口
	virtual JZ_RESULT SetViewPort(JZViewPort* pViewPort) = 0;
	// 获取当前视口
	virtual JZ_RESULT GetViewPort(JZViewPort* pViewPort) = 0;
	// 设置alpha混叠状态
	virtual JZ_RESULT SetAlphaBlendStatus(JZAlphaBlendDesc* pAlphaBlend) = 0;
	// 设置深度模板测试状态
	virtual JZ_RESULT SetDepthStencilStatus(JZDepthStencilDesc* pDepthStencil) = 0;
	// 设置面剔除状态
	virtual JZ_RESULT SetRasterizerStatus(JZRasterizerDesc* pRasterDesc) = 0;
};

// OpenGL的shader资源
class IJZShader : public IJZBaseRes
{
public:
	// 获取资源类型
	virtual JZ_RES_TYPE GetResType() = 0;
	// 使用着色器程序
	virtual void Use() = 0;
	// 解除使用着色器程序
	virtual void UnUse() = 0;
	// shaderName表示包含了shader路径的字符串数组，iShaderNums表示该字符串数组包含了几个shader路径，字符串数组应该按照顶点着色器、片段着色器、几何着色器的顺序排列
	virtual JZ_RESULT Create(const char** shaderName, int iShaderNums) = 0;
	virtual JZ_RESULT Create(JZShaderInfo* shaders, int iShaderNums) = 0;
	// 获取着色器程序ID
	virtual unsigned int GetProgramID() = 0;
	// 释放着色器程序
	virtual void Release() = 0;
	// 获取shader中uniform参数的位置
	virtual unsigned int GetParamLoc(IN const char* paramName, IN OUT unsigned int* pParamLoc = NULL) = 0;
	// 获取shader中子函数的索引
	virtual unsigned int GetSubroutineIndex(IN const char* subroutineName, IN JZ_SHADER_TYPE shaderType, IN OUT unsigned int* pSubIndex) = 0;
	// 设置shader中要调用的子函数索引
	virtual bool SetSubroutineIndex(IN unsigned int subIndex, IN JZ_SHADER_TYPE shaderType) = 0;
	// 设置shader中unform参数的值
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

// OpenGL纹理资源
class IJZTexture : public IJZBaseRes
{
public:
	// 获取资源类型
	virtual JZ_RES_TYPE GetResType() = 0;
	// 创建纹理资源，目前仅支持RGB图像
	virtual JZ_RESULT Create(JZTextureDesc* pTexDesc) = 0;
	// 释放纹理资源
	virtual JZ_RESULT Release() = 0;
	// 往纹理中填充图像数据，目前只支持和已经创建的纹理宽高一样的情况，该接口慎用
	virtual JZ_RESULT FillImage(JZImageBuf* pImageBuf) = 0;
	// 将纹理写入到图片文件，仅支持bmp图像格式
	//virtual bool Dump(const char* filepath) = 0;
	// 获取该纹理ID
	virtual unsigned int GetTexID() = 0;
	// 获取深度纹理ID
	virtual unsigned int GetTexDepthID() = 0;
	// 获取纹理宽度
	virtual int GetTexWidth() = 0;
	// 获取纹理高度
	virtual int GetTexHeight() = 0;
};

// OpenGL网格资源
class IJZMesh : public IJZBaseRes
{
public:
	// 获取资源类型
	virtual JZ_RES_TYPE GetResType() = 0;
	// 根据网格描述来创建网格资源
	virtual JZ_RESULT CreateMesh(JZMeshDesc* pMeshDesc) = 0;
	// 创建用于显示图像的网格资源
	virtual JZ_RESULT CreateQuadMesh() = 0;
	// 根据绘制区域的宽高比和纹理宽高比创建网格资源
	virtual JZ_RESULT CreateQuadMesh(float rectAspect, float texAspect) = 0;
	// 释放网格资源
	virtual JZ_RESULT Release() = 0;
	// 绘制网格
	//virtual JZ_RESULT Draw() = 0;
	// 绘制网格
	virtual JZ_RESULT Draw(UINT uStartIndexLocation = 0, UINT uIndexCount = 0) = 0;
};

// OpenGL摄像机系统
class IJZCamera
{
public:
	// 设置相机位置
	virtual void SetCameraPos(glm::vec3 position) = 0;
	// 设置相机角度参数为-1时，表示保持原参数不变
	virtual void SetCameraAngle(float pitch = -1, float yaw = -1, float roll = -1) = 0;
	// 设置相机方向
	virtual void SetCameraVec(glm::vec3 front) = 0;
	// 获取视图矩阵
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