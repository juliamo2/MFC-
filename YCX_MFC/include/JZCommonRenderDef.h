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

// shader����
enum JZ_SHADER_TYPE
{
	JZ_SHADER_UNKNOW,
	JZ_SHADER_VERTEX,		// ������ɫ��
	JZ_SHADER_CONTROL,		// ϸ�ֿ�����ɫ��
	JZ_SHADER_EVALUATION,	// ϸ�ּ�����ɫ��
	JZ_SHADER_GEOMETRY,		// ������ɫ��
	JZ_SHADER_FRAGMENT,		// Ƭ����ɫ��
	JZ_SHADER_COMPUTE,		// ������ɫ��
	
};

typedef struct tag_JZShaderInfo
{
	const char* filename;
	JZ_SHADER_TYPE type;
}JZShaderInfo;

// �������������
typedef struct tag_JZTexSampDesc
{
	int				nIndex;
	unsigned int	uiActiveIndex;	// �����Ԫ����������ȡGL_TEXTURE0��GL_TEXTRUE15

	/*UINT			uStartSlot;
	UINT			uNumSampler;*/

	unsigned int	uiTexWrapS;		// ����ˮƽ����Ļ��Ʒ�ʽ����ȡGL_REPEAT��GL_MIRRORED_REPEAT��GL_CLAMP_TO_EDGE��GL_CLAMP_TO_BORDER
	unsigned int	uiTexWrapT;		// ����ֱ����Ļ��Ʒ�ʽ
	unsigned int	uiTexWrapR;		// ����3D��������Z����Ļ��Ʒ�ʽ
	DWORD			dwBorderColor;	// �����Ʒ�ʽΪGL_CLAMP_TO_BORDER���û�ָ���ı߽���ɫ����0xffffffffΪ��ɫ

	unsigned int	uiMinFilter;	// ������Сʱ�Ĺ��˷�ʽ����ȡGL_NEAREST��GL_LINEAR��GL_LINEAR_MIPMAP_LINEAR��
	unsigned int	uiMagFilter;	// ����Ŵ�ʱ�Ĺ��˷�ʽ
	unsigned int	uiMipFilter;	// �༶��Զ����Ĺ��˷�ʽ
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
	JZ_TEXUSAGE_COMMON,				// ��ͨ������;
	JZ_TEXUSAGE_DEPTHSTENCIL,		// ���ģ��������;
};

typedef struct tag_JZTextureDesc
{
	unsigned int						width;		// �����
	unsigned int						height;		// �����
	unsigned int						depth;		
	unsigned int						format;		// ָ������ڲ���ʽ�����ģ������һ��ȡGL_DEPTH24_STENCIL8
	JZ_TEXTURE_USAGE					usage;		// ������;
	const char*							filepath;	// ͼ���ļ�·��
	JZImageBuf*							pImageBuf;	// ���ڴ��������ͼ������
	bool								bVolume;	
	unsigned int						uiTexId;	// �ⲿ����������ID���ڲ�ֱ��ʹ��								

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

// ����������;
enum JZ_ATTRI_USAGE
{
	JZ_POSITION,		// λ������
	JZ_COLOR,			// ��ɫ
	JZ_TEXCOORD,		// ��������
	JZ_NORMAL,			// ����
};

// ����һ��������һ���������ݵĽṹ��
typedef struct tag_JZVBAttri
{
	JZ_ATTRI_USAGE		_attriUsage;// �����Ե���;
	unsigned int		_offset;	// ���Ե���ʼ��ַ ����� ������ʼ��ַ ��ƫ����
	unsigned int		_eType;		// ������һ��Ԫ�ص��������ͣ�һ��ȡGL_FLOAT
	unsigned int		_nElem;		// �����а�����Ԫ�ظ���
	void SetDefault()
	{
		_offset = 0;
		_eType = GL_FLOAT;
		_nElem = 0;
	}
}JZVBAttri;

// ��������
typedef struct tag_JZMeshDesc
{
	// ���±���
	// Base Data
	unsigned int	_nPrimitType;	// OpenGL����ͼԪ���ͣ���ȡGL_POINTS��GL_LINES��GL_LINE_STRIP��GL_LINE_LOOP��GL_TRIANGLES��GL_TRIANGLE_STRIP��GL_TRIANGLE_FAN

	JZVBAttri*		_pVBAttri;		// һ����������������������ʼ��ַ
	int				_nVBAttri;		// һ��������������Եĸ���	
	void*			_pCVBData;		// �������ݵ���ʼ��ַ��CPU���ݣ�
	unsigned int	_uVBSize;		// �������ݵĴ�С�����ֽ����ƣ�
	unsigned int	_uVBStride;		// �������ݣ������������ԣ��Ŀ�ȣ����ֽڼƣ�

	void*			_pCIBData;		// �����������ݵ���ʼ��ַ��CPU���ݣ�
	unsigned int	_uIBSize;		// �����������ݵĴ�С(���ֽڼ�)��ע����������֮��Ŀ��Ϊsizeof(unsigned int)

	// Ĭ�Ϲ��캯��
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
	// ��ֵ������
	tag_JZMeshDesc& operator = (const tag_JZMeshDesc& meshDesc)
	{
		if (this == &meshDesc) // ����Լ����Լ���ֵ��ֱ�ӷ���
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
	// �������캯��
	tag_JZMeshDesc(const tag_JZMeshDesc& meshDesc)
	{
		*this = meshDesc;	//�������غ��"=" 
	}
} JZMeshDesc;

// alpha�������
typedef struct tag_JZAlphaBlendDesc
{
	bool						bEnable;			// alpha������� 
	unsigned int				srcBlend;			// Դ��ɫ�Ļ�����ӣ���ȡGL_ZERO��GL_ONE��GL_SRC_ALPHA��GL_ONE_MINUS_SRC_ALPHA��
	unsigned int				dstBlend;			// Ŀ����ɫ�Ļ�����ӣ���ȡGL_ZERO��GL_ONE��GL_SRC_ALPHA��GL_ONE_MINUS_SRC_ALPHA��
	unsigned int				blendFunc;			// ��ɫ�Ļ�Ϻ�������ȡGL_FUNC_ADD��GL_FUNC_SUBTRACT��GL_FUNC_REVERSE_SUBTRACT��GL_MIN��GL_MAX
	unsigned int				srcBlendAlpha;		// Դalpha�Ļ�����ӣ���ȡGL_ZERO��GL_ONE��GL_SRC_ALPHA��GL_ONE_MINUS_SRC_ALPHA��
	unsigned int				dstBlendAlpha;		// Ŀ��alpha�Ļ�����ӣ���ȡGL_ZERO��GL_ONE��GL_SRC_ALPHA��GL_ONE_MINUS_SRC_ALPHA��
	unsigned int				blendFuncAlpha;		// alpha�Ļ�Ϻ�������ȡGL_FUNC_ADD��GL_FUNC_SUBTRACT��GL_FUNC_REVERSE_SUBTRACT��GL_MIN��GL_MAX
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

// ���ģ���������
typedef struct tag_JZDepthStencilDesc
{
	bool						bDepthEnable;		//	��Ȼ��濪��
	bool						bDepthWrite;		//	�����Ϣ��д��
	unsigned int				depthFunc;			//	Ĭ��:less

	bool						bStencilEnable;		//	ģ����Կ���
	
	// glStencilFunc()��������������
	unsigned int				stencilFunc;		//	ģ����Թ���
	int							stencilRef;			//	ģ���������ֵ[0, 2^n - 1] n ��ģ�建���λ��
	unsigned int				mask;				//	��ʾһ��ģ��, ������refֵ�Լ�ģ��ֵ��������, ��ʼ��1

	unsigned int				stencilFuncFace;	//	ָ��ģ�����״̬������ Ĭ��:Front
	
	// glStencilOp()�����������������ú�������ģ�建����α仯
	unsigned int				stencilFail;		//	��ģ�����ʧ��ʱ
	unsigned int				depthFail;			//	��ģ����Գɹ�,��Ȳ���ʧ��ʱ
	unsigned int				depthPass;			//	��ģ����Ժ���Ȳ��Զ��ɹ�����, ģ����Ի���Ȳ�������֮һ���ڲ��ɹ�

	unsigned int				stencilOpFace;		//	ָ��ģ����Ը�����
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
	bool						bCullEnable;			// ���޳�����
	unsigned int				frontFace;				// ���������棬�Լ����Ʒ�ʽ��GL_CW��ʾ��ʱ����Ϊ�����棬GL_CCW��ʾ˳ʱ����Ϊ������
	unsigned int				cullFace;				// �޳���, ��ʾ�棬GL_BACK��ʾֻ�޳������棬GL_FRONT��ʾֻ�޳������棬GL_FRONT_AND_BACK��ʾ�޳�������ͱ�����
	// glPolygonMode�������������������ƶ���ε���ʾ��ʽ
	unsigned int				polygonMode;			// �������ʾģʽ��GL_POINT��ʾ��ʾ�㣬GL_LINE��ʾ��ʾ�ߣ�GL_FILL��ʾ��ʾ��
	unsigned int				polygonFace;			// ���ڿ��ƶ���ε���ʾģʽ��������Щ�棬GL_BACK��ʾ�����ڱ����棬GL_FRONT��ʾ�����������棬GL_FRONT_AND_BACK��ʾ������������ͱ�����
	

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
	unsigned int				uTopLeftX;				// ���ϽǶ���X���� 
	unsigned int				uTopLeftY;				// ���ϽǶ���Y����
	unsigned int				uWidth;					// ��
	unsigned int				uHeight;				// ��
	tag_JZViewPort()
	{
		uTopLeftX				= 0;
		uTopLeftY				= 0;
		uWidth					= 0;
		uHeight					= 0;
	}
}JZViewPort;

#endif // !__JZ_COMMONRENDERDEF_H__

