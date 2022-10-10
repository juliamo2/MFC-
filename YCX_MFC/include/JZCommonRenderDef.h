#ifndef __JZ_COMMONRENDERDEF_H__
#define __JZ_COMMONRENDERDEF_H__
#include <JZCommonImageDef.h>
#include <GL/glew.h>
#include <cassert>

inline bool glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	if ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		assert(0);
	}
	return true;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

// shader类型
enum JZ_SHADER_TYPE
{
	JZ_SHADER_UNKNOW,
	JZ_SHADER_VERTEX,		// 顶点着色器
	JZ_SHADER_CONTROL,		// 细分控制着色器
	JZ_SHADER_EVALUATION,	// 细分计算着色器
	JZ_SHADER_GEOMETRY,		// 几何着色器
	JZ_SHADER_FRAGMENT,		// 片段着色器
	JZ_SHADER_COMPUTE,		// 计算着色器
	
};

typedef struct tag_JZShaderInfo
{
	const char* filename;
	JZ_SHADER_TYPE type;
}JZShaderInfo;

// 描述纹理采样器
typedef struct tag_JZTexSampDesc
{
	int				nIndex;
	unsigned int	uiActiveIndex;	// 纹理激活单元的索引，可取GL_TEXTURE0到GL_TEXTRUE15

	/*UINT			uStartSlot;
	UINT			uNumSampler;*/

	unsigned int	uiTexWrapS;		// 纹理水平方向的环绕方式，可取GL_REPEAT，GL_MIRRORED_REPEAT，GL_CLAMP_TO_EDGE，GL_CLAMP_TO_BORDER
	unsigned int	uiTexWrapT;		// 纹理垂直方向的环绕方式
	unsigned int	uiTexWrapR;		// 对于3D纹理，纹理Z方向的环绕方式
	DWORD			dwBorderColor;	// 当环绕方式为GL_CLAMP_TO_BORDER，用户指定的边界颜色，如0xffffffff为白色

	unsigned int	uiMinFilter;	// 纹理缩小时的过滤方式，可取GL_NEAREST，GL_LINEAR，GL_LINEAR_MIPMAP_LINEAR等
	unsigned int	uiMagFilter;	// 纹理放大时的过滤方式
	unsigned int	uiMipFilter;	// 多级渐远纹理的过滤方式
	/*float			fMipMapLobBias;
	float			fMaxANISOTROPY;*/

	tag_JZTexSampDesc()
	{
		/*uStartSlot = 0;
		uNumSampler = 1;*/
		uiTexWrapS = GL_REPEAT;
		uiTexWrapT = GL_REPEAT;
		uiTexWrapR = GL_REPEAT;
		dwBorderColor = 0x00000000;
		uiMinFilter = GL_NEAREST;
		uiMagFilter = GL_NEAREST;
		uiMipFilter = GL_NEAREST;
		/*fMipMapLobBias = 0.f;
		fMaxANISOTROPY = 16.f;*/
		nIndex = 0;
	}
}JZTexSampDesc;

enum JZ_TEXTURE_USAGE
{
	JZ_TEXUSAGE_COMMON,				// 普通纹理用途
	JZ_TEXUSAGE_DEPTHSTENCIL,		// 深度模板纹理用途
};

typedef struct tag_JZTextureDesc
{
	unsigned int						width;		// 纹理宽
	unsigned int						height;		// 纹理高
	unsigned int						depth;		
	unsigned int						format;		// 指纹理的内部格式，深度模板纹理一般取GL_DEPTH24_STENCIL8
	JZ_TEXTURE_USAGE					usage;		// 纹理用途
	const char*							filepath;	// 图像文件路径
	JZImageBuf*							pImageBuf;	// 用于创建纹理的图像数据
	bool								bVolume;	
	unsigned int						uiTexId;	// 外部创建的纹理ID，内部直接使用								

	tag_JZTextureDesc()
	{
		width = 0;
		height = 0;
		depth = 1;
		format = GL_RGBA;
		usage = JZ_TEXUSAGE_COMMON;
		filepath = NULL;
		pImageBuf = NULL;
		bVolume = FALSE;
		uiTexId = 0;
	}
}JZTextureDesc;

// 顶点属性用途
enum JZ_ATTRI_USAGE
{
	JZ_POSITION,		// 位置坐标
	JZ_COLOR,			// 颜色
	JZ_TEXCOORD,		// 纹理坐标
	JZ_NORMAL,			// 法线
};

// 描述一个顶点中一个属性数据的结构体
typedef struct tag_JZVBAttri
{
	JZ_ATTRI_USAGE		_attriUsage;// 该属性的用途
	unsigned int		_offset;	// 属性的起始地址 相对于 顶点起始地址 的偏移量
	unsigned int		_eType;		// 属性中一个元素的数据类型，一般取GL_FLOAT
	unsigned int		_nElem;		// 属性中包含的元素个数
	void SetDefault()
	{
		_offset = 0;
		_eType = GL_FLOAT;
		_nElem = 0;
	}
}JZVBAttri;

// 网格描述
typedef struct tag_JZMeshDesc
{
	// 以下必填
	// Base Data
	unsigned int	_nPrimitType;	// OpenGL几何图元类型，可取GL_POINTS、GL_LINES、GL_LINE_STRIP、GL_LINE_LOOP、GL_TRIANGLES、GL_TRIANGLE_STRIP、GL_TRIANGLE_FAN

	JZVBAttri*		_pVBAttri;		// 一个顶点包含的属性数组的起始地址
	int				_nVBAttri;		// 一个顶点包含的属性的个数	
	void*			_pCVBData;		// 顶点数据的起始地址（CPU数据）
	unsigned int	_uVBSize;		// 顶点数据的大小（按字节数计）
	unsigned int	_uVBStride;		// 顶点数据（包含所有属性）的跨度（按字节计）

	void*			_pCIBData;		// 顶点索引数据的起始地址（CPU数据）
	unsigned int	_uIBSize;		// 顶点索引数据的大小(按字节计)，注：两个索引之间的跨度为sizeof(unsigned int)

	// 默认构造函数
	tag_JZMeshDesc()
	{
		_nPrimitType = GL_TRIANGLES;

		_pVBAttri = NULL;
		_nVBAttri = 0;
		_pCVBData = NULL;
		_uVBSize = 0;
		_uVBStride = 0;

		_pCIBData = NULL;
		_uIBSize = 0;
	}
	// 赋值符重载
	tag_JZMeshDesc& operator = (const tag_JZMeshDesc& meshDesc)
	{
		if (this == &meshDesc) // 如果自己给自己赋值则直接返回
			return *this;
		_pVBAttri = meshDesc._pVBAttri;
		_nVBAttri = meshDesc._nVBAttri;
		_nPrimitType = meshDesc._nPrimitType;
		_pCVBData = meshDesc._pCVBData;
		_uVBSize = meshDesc._uVBSize;
		_uVBStride = meshDesc._uVBStride;
		_pCIBData = meshDesc._pCIBData;
		_uIBSize = meshDesc._uIBSize;
		return *this;
	}
	// 拷贝构造函数
	tag_JZMeshDesc(const tag_JZMeshDesc& meshDesc)
	{
		*this = meshDesc;	//调用重载后的"=" 
	}
} JZMeshDesc;

// alpha混叠描述
typedef struct tag_JZAlphaBlendDesc
{
	bool						bEnable;			// alpha混叠开关 
	unsigned int				srcBlend;			// 源颜色的混合因子，可取GL_ZERO、GL_ONE、GL_SRC_ALPHA、GL_ONE_MINUS_SRC_ALPHA等
	unsigned int				dstBlend;			// 目标颜色的混合因子，可取GL_ZERO、GL_ONE、GL_SRC_ALPHA、GL_ONE_MINUS_SRC_ALPHA等
	unsigned int				blendFunc;			// 颜色的混合函数，可取GL_FUNC_ADD、GL_FUNC_SUBTRACT、GL_FUNC_REVERSE_SUBTRACT、GL_MIN、GL_MAX
	unsigned int				srcBlendAlpha;		// 源alpha的混合因子，可取GL_ZERO、GL_ONE、GL_SRC_ALPHA、GL_ONE_MINUS_SRC_ALPHA等
	unsigned int				dstBlendAlpha;		// 目标alpha的混合因子，可取GL_ZERO、GL_ONE、GL_SRC_ALPHA、GL_ONE_MINUS_SRC_ALPHA等
	unsigned int				blendFuncAlpha;		// alpha的混合函数，可取GL_FUNC_ADD、GL_FUNC_SUBTRACT、GL_FUNC_REVERSE_SUBTRACT、GL_MIN、GL_MAX
	tag_JZAlphaBlendDesc()
	{
		bEnable					= true;

		srcBlend				= GL_SRC_ALPHA;				//	src rgb
		dstBlend				= GL_ONE_MINUS_SRC_ALPHA;	//	dst rgb
		blendFunc				= GL_FUNC_ADD;

		srcBlendAlpha			= GL_ONE;					//	src alpha
		dstBlendAlpha			= GL_ONE_MINUS_SRC_ALPHA;	//	dst alpha
		blendFuncAlpha			= GL_FUNC_ADD;
	}
}JZAlphaBlendDesc;

// 深度模板测试描述
typedef struct tag_JZDepthStencilDesc
{
	bool						bDepthEnable;		//	深度缓存开关
	bool						bDepthWrite;		//	深度信息的写入
	unsigned int				depthFunc;			//	默认:less

	bool						bStencilEnable;		//	模板测试开关
	
	// glStencilFunc()函数的三个参数
	unsigned int				stencilFunc;		//	模板测试功能
	int							stencilRef;			//	模板测试引用值[0, 2^n - 1] n 是模板缓存的位数
	unsigned int				mask;				//	表示一个模板, 用来和ref值以及模板值做与运算, 初始化1

	unsigned int				stencilFuncFace;	//	指定模板测试状态更新面 默认:Front
	
	// glStencilOp()函数的三个参数，该函数描述模板缓存如何变化
	unsigned int				stencilFail;		//	当模板测试失败时
	unsigned int				depthFail;			//	当模板测试成功,深度测试失败时
	unsigned int				depthPass;			//	当模板测试和深度测试都成功或者, 模板测试或深度测试其中之一存在并成功

	unsigned int				stencilOpFace;		//	指定模板测试更新面
	tag_JZDepthStencilDesc()
	{
		bDepthEnable			= true;
		bDepthWrite				= true;
		depthFunc				= GL_LESS;

		bStencilEnable			= true;

		stencilFunc				= GL_ALWAYS;
		stencilRef				= 1;
		mask					= 0xFF;
		stencilFuncFace			= GL_FRONT;

		stencilOpFace			= GL_FRONT;
		stencilFail				= GL_KEEP;
		depthFail				= GL_KEEP;
		depthPass				= GL_REPLACE;
	}
}JZDepthStencilDesc;

typedef struct tag_JZRasterizerDesc
{
	bool						bCullEnable;			// 面剔除开关
	unsigned int				frontFace;				// 设置正向面，以及绘制方式，GL_CW表示逆时针面为正向面，GL_CCW表示顺时针面为正香面
	unsigned int				cullFace;				// 剔除面, 显示面，GL_BACK表示只剔除背向面，GL_FRONT表示只剔除正向面，GL_FRONT_AND_BACK表示剔除正向面和背向面
	// glPolygonMode函数的两个参数，控制多边形的显示方式
	unsigned int				polygonMode;			// 多边形显示模式，GL_POINT表示显示点，GL_LINE表示显示线，GL_FILL表示显示面
	unsigned int				polygonFace;			// 用于控制多边形的显示模式适用于哪些面，GL_BACK表示适用于背向面，GL_FRONT表示适用于正向面，GL_FRONT_AND_BACK表示适用于正向面和背向面
	

	tag_JZRasterizerDesc()
	{
		bCullEnable				= true;
		frontFace				= GL_CW;
		cullFace				= GL_BACK;
		polygonMode				= GL_FILL;
		polygonFace				= GL_FRONT_AND_BACK;
	}
}JZRasterizerDesc;

typedef struct tag_JZViewPort
{
	unsigned int				uTopLeftX;				// 左上角顶点X坐标 
	unsigned int				uTopLeftY;				// 左上角顶点Y坐标
	unsigned int				uWidth;					// 宽
	unsigned int				uHeight;				// 高
	tag_JZViewPort()
	{
		uTopLeftX				= 0;
		uTopLeftY				= 0;
		uWidth					= 0;
		uHeight					= 0;
	}
}JZViewPort;

#endif // !__JZ_COMMONRENDERDEF_H__

