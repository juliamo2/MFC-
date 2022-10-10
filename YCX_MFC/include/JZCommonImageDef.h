#ifndef __JZ_COMMONIMAGEDEF_H__
#define __JZ_COMMONIMAGEDEF_H__
#include <vector>
#include <string>
#include <JZCommonDef.h>

// ���ظ�ʽ��Ŀǰ��֧�ִ�����ظ�ʽ����Ƭ���ظ�ʽ�Ժ���չ
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
	unsigned char*		color;			// ��ɫͨ��
	int					pitch;			// ��ɫͨ��һ�е��ֽ���
	unsigned char*		color_U;		// U ��Ƭ����
	int					u_Pitch;		// U ��Ƭ����һ�е��ֽ���
	unsigned char*		color_V;		// V ��Ƭ����
	int					v_Pitch;		// V ��Ƭ����һ�е��ֽ���
	unsigned char*		alpha;			// A ͨ�����������ظ�ʽδ�ã��粻�� A �����޷���� A ͨ����
	int					a_Pitch;		// A ͨ��һ�е��ֽ���
	JZ_PIXEL_FMT		pixel_fmt;		// ���ظ�ʽ
	int					width;			// ͼ����
	int					height;			// ͼ��߶�

}JZImageBuf;

// ͼ�������洢������
typedef struct tag_JZImageProcessExtraData
{
	std::vector<std::string>	vecPlateStrs;		// ���ڴ洢ʶ����ĳ����ַ���
}JZImageProcessExtraData;

// ͼ��������(Դ)buffer�����(Ŀ��)buffer
typedef struct tag_JZImageProcessData
{
	JZImageBuf*					pSrcImage;			// Ҫ����ͼ�����buffer
	JZImageBuf*					pDesImage;			// ���ڴ洢ͼ������buffer
	std::vector<std::string>	vecPlateStrs;		// ���ڴ洢ʶ����ĳ����ַ���
	JZImageProcessExtraData*	pExtraData;			// �洢��������
}JZImageProcessData;

// ͼ��������
enum JZ_IMAGEPROC_TYPE
{
	JZ_IMAGE_UNKNOWN = -1,
	JZ_IMAGE_BASEPROCESS,
	JZ_IMAGE_PLATERECOG,
	
};

// ͼ�����һЩ�����Ĺ�������
struct JZCommonParam
{
	JZ_IMAGEPROC_TYPE processType;
	JZCommonParam()
	{
		processType = JZ_IMAGE_UNKNOWN;
	}
};

// ����ͼ��������
enum JZ_BASEPROCESS_TYPE
{
	JZ_BASEPROCESS_UNKNOWN,
	JZ_BASEPROCESS_SMOOTH,		// ͼ��ƽ��
	JZ_BASEPROCESS_MORPHOLOGY,	// ͼ����̬ѧ
	JZ_BASEPROCESS_HISTOGRAM,	// ͼ��ֱ��ͼ
};

// ����ͼ�������
typedef struct tag_JZBaseProcessParam : public JZCommonParam
{
	JZ_BASEPROCESS_TYPE baseProcessType;
	tag_JZBaseProcessParam()
	{
		processType		= JZ_IMAGE_BASEPROCESS;
		baseProcessType = JZ_BASEPROCESS_UNKNOWN;
	}
}JZBaseProcessParam;

// ͼ��ƽ����������
enum JZ_SMOOTH_TYPE
{
	JZ_SMOOTH_GAUSSIAN = 0,		// ��˹�˲�
	JZ_SMOOTH_MEAN,				// ��ֵ�˲�
	JZ_SMOOTH_MEDIAN,			// ��ֵ�˲�
	JZ_SMOOTH_BILATERAL,		// ˫���˲�
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

// ͼ����̬ѧ�����������
enum JZ_MORPHOLOGY_TYPE
{
	JZ_MORPHOLOGY_ERODE,		// ��ʴ
	JZ_MORPHOLOGY_DILATE,		// ����
	JZ_MORPHOLOGY_OPEN,			// ������
	JZ_MORPHOLOGY_CLOSE,		// ������
	JZ_MORPHOLOGY_GRADIENT,		// ��̬ѧ�ݶ�
	JZ_MORPHOLOGY_TOPHAT,		// ��ñ
	JZ_MORPHOLOGY_BLACKHAT,		// ��ñ
	JZ_MORPHOLOGY_HITMISS,		// ���л�����

};

enum JZ_MORPHOLOGY_SHAPE
{
	JZ_MORPHOLOGY_RECT,			// ����
	JZ_MORPHOLOGY_CROSS,		// ������
	JZ_MORPHOLOGY_ELLIPSE,		// ��Բ��
};

// ��̬ѧ�������
typedef struct tag_JZMorphologyParam: public JZBaseProcessParam
{
	JZ_MORPHOLOGY_TYPE		morphologyType;		// ��̬ѧ����
	JZ_MORPHOLOGY_SHAPE		morphologyShape;	// ��̬ѧ�ṹԪ����״
	int						width;				// �ṹԪ�ؿ�				
	int						height;				// �ṹԪ�ظ�
	tag_JZMorphologyParam()
	{
		baseProcessType		= JZ_BASEPROCESS_MORPHOLOGY;
		morphologyType		= JZ_MORPHOLOGY_ERODE;
		morphologyShape		= JZ_MORPHOLOGY_RECT;
		width				= 3;
		height				= 3;
	}
}JZMorphologyParam;

// ֱ��ͼ�������
typedef struct tag_JZHistogramParam : public JZBaseProcessParam
{
	bool					bIsBGRHist;			// Ϊtrue��ʾ��BGRֱ��ͼ��Ϊfalseʱ����ʾ��HSVֱ��ͼ
	tag_JZHistogramParam()
	{
		baseProcessType = JZ_BASEPROCESS_HISTOGRAM;
		bIsBGRHist = true;
	}
}JZHistogramParam;

// ����ʶ�����
typedef struct tag_JZPlateRecogParam : public JZCommonParam
{
	tag_JZPlateRecogParam()
	{
		processType = JZ_IMAGE_PLATERECOG;
	}
}JZPlateRecogParam;

#endif // !__JZ_COMMONIMAGEDEF_H__
