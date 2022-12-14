#ifndef __JZ_COMMONIMAGEDEF_H__
#define __JZ_COMMONIMAGEDEF_H__
#include <vector>
#include <string>
#include <JZCommonDef.h>

// 像素格式，目前仅支持打包像素格式，分片像素格式以后扩展
enum JZ_PIXEL_FMT
{
	JZ_PIXFMT_BGR,
	JZ_PIXFMT_RGB,
	JZ_PIXFMT_BGRA,
	JZ_PIXFMT_RGBA,
	JZ_PIXFMT_YUVA,
};

typedef struct tag_JZImageBuf
{
	unsigned char*		color;			// 颜色通道
	int					pitch;			// 颜色通道一行的字节数
	unsigned char*		color_U;		// U 分片数据
	int					u_Pitch;		// U 分片数据一行的字节数
	unsigned char*		color_V;		// V 分片数据
	int					v_Pitch;		// V 分片数据一行的字节数
	unsigned char*		alpha;			// A 通道，部分像素格式未用（如不含 A 或者无分离的 A 通道）
	int					a_Pitch;		// A 通道一行的字节数
	JZ_PIXEL_FMT		pixel_fmt;		// 像素格式
	int					width;			// 图像宽度
	int					height;			// 图像高度

}JZImageBuf;

// 图像处理额外存储的数据
typedef struct tag_JZImageProcessExtraData
{
	std::vector<std::string>	vecPlateStrs;		// 用于存储识别出的车牌字符串
}JZImageProcessExtraData;

// 图像处理输入(源)buffer和输出(目的)buffer
typedef struct tag_JZImageProcessData
{
	JZImageBuf*					pSrcImage;			// 要进行图像处理的buffer
	JZImageBuf*					pDesImage;			// 用于存储图像处理后的buffer
	std::vector<std::string>	vecPlateStrs;		// 用于存储识别出的车牌字符串
	JZImageProcessExtraData*	pExtraData;			// 存储额外数据
}JZImageProcessData;

// 图像处理类型
enum JZ_IMAGEPROC_TYPE
{
	JZ_IMAGE_UNKNOWN = -1,
	JZ_IMAGE_BASEPROCESS,
	JZ_IMAGE_PLATERECOG,
	
};

// 图像处理的一些基本的公共参数
struct JZCommonParam
{
	JZ_IMAGEPROC_TYPE processType;
	JZCommonParam()
	{
		processType = JZ_IMAGE_UNKNOWN;
	}
};

// 基本图像处理类型
enum JZ_BASEPROCESS_TYPE
{
	JZ_BASEPROCESS_UNKNOWN,
	JZ_BASEPROCESS_SMOOTH,		// 图像平滑
	JZ_BASEPROCESS_MORPHOLOGY,	// 图像形态学
	JZ_BASEPROCESS_HISTOGRAM,	// 图像直方图
};

// 基本图像处理参数
typedef struct tag_JZBaseProcessParam : public JZCommonParam
{
	JZ_BASEPROCESS_TYPE baseProcessType;
	tag_JZBaseProcessParam()
	{
		processType		= JZ_IMAGE_BASEPROCESS;
		baseProcessType = JZ_BASEPROCESS_UNKNOWN;
	}
}JZBaseProcessParam;

// 图像平滑基本参数
enum JZ_SMOOTH_TYPE
{
	JZ_SMOOTH_GAUSSIAN = 0,		// 高斯滤波
	JZ_SMOOTH_MEAN,				// 均值滤波
	JZ_SMOOTH_MEDIAN,			// 中值滤波
	JZ_SMOOTH_BILATERAL,		// 双边滤波
};

typedef struct tag_JZSmoothParam : public JZBaseProcessParam
{
	JZ_SMOOTH_TYPE smoothType;
	tag_JZSmoothParam()
	{
		baseProcessType = JZ_BASEPROCESS_SMOOTH;
		smoothType		= JZ_SMOOTH_GAUSSIAN;
	}
}JZSmoothParam;

// 图像形态学处理基本参数
enum JZ_MORPHOLOGY_TYPE
{
	JZ_MORPHOLOGY_ERODE,		// 腐蚀
	JZ_MORPHOLOGY_DILATE,		// 膨胀
	JZ_MORPHOLOGY_OPEN,			// 开运算
	JZ_MORPHOLOGY_CLOSE,		// 闭运算
	JZ_MORPHOLOGY_GRADIENT,		// 形态学梯度
	JZ_MORPHOLOGY_TOPHAT,		// 顶帽
	JZ_MORPHOLOGY_BLACKHAT,		// 黑帽
	JZ_MORPHOLOGY_HITMISS,		// 击中击不中

};

enum JZ_MORPHOLOGY_SHAPE
{
	JZ_MORPHOLOGY_RECT,			// 矩形
	JZ_MORPHOLOGY_CROSS,		// 交叉形
	JZ_MORPHOLOGY_ELLIPSE,		// 椭圆形
};

// 形态学处理参数
typedef struct tag_JZMorphologyParam: public JZBaseProcessParam
{
	JZ_MORPHOLOGY_TYPE		morphologyType;		// 形态学类型
	JZ_MORPHOLOGY_SHAPE		morphologyShape;	// 形态学结构元素形状
	int						width;				// 结构元素宽				
	int						height;				// 结构元素高
	tag_JZMorphologyParam()
	{
		baseProcessType		= JZ_BASEPROCESS_MORPHOLOGY;
		morphologyType		= JZ_MORPHOLOGY_ERODE;
		morphologyShape		= JZ_MORPHOLOGY_RECT;
		width				= 3;
		height				= 3;
	}
}JZMorphologyParam;

// 直方图处理参数
typedef struct tag_JZHistogramParam : public JZBaseProcessParam
{
	bool					bIsBGRHist;			// 为true表示是BGR直方图，为false时，表示是HSV直方图
	tag_JZHistogramParam()
	{
		baseProcessType = JZ_BASEPROCESS_HISTOGRAM;
		bIsBGRHist = true;
	}
}JZHistogramParam;

// 车牌识别参数
typedef struct tag_JZPlateRecogParam : public JZCommonParam
{
	tag_JZPlateRecogParam()
	{
		processType = JZ_IMAGE_PLATERECOG;
	}
}JZPlateRecogParam;

#endif // !__JZ_COMMONIMAGEDEF_H__
