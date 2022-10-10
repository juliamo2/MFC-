#ifndef EASYPR_CONFIG_H_
#define EASYPR_CONFIG_H_

#define CV_VERSION_THREE_TWO
#include "opencv2/opencv.hpp"
namespace easypr
{

	enum Color { BLUE, YELLOW, WHITE, UNKNOWN };	// ��ɫ����

	enum LocateType { SOBEL, COLOR, CMSER, OTHER }; // ��λ��ʽ

	enum CharSearchDirection { LEFT, RIGHT };		// �ַ���������

	// PR���ó���ģʽ
	enum
	{
		PR_MODE_UNCONSTRAINED,	// ��Լ��
		PR_MODE_CAMERPOHNE,		// ���
		PR_MODE_PARKING,		// ͣ����
		PR_MODE_HIGHWAY			// ���ٹ�·
	};

	enum
	{
		PR_DETECT_SOBEL = 0x01,  /**Sobel detect type, using twice Sobel  */
		PR_DETECT_COLOR = 0x02,  /**Color detect type   */
		PR_DETECT_CMSER = 0x04,  /**Character detect type, using mser  */
	};

	static const char* kDefaultSvmFile = "svm_hist.xml";
	static const char* kLBPSvmFile = "svm_lbp.xml";
	static const char* kHistSvmFile = "svm_hist.xml";

	static const char* kDefaultAnnFile = "ann.xml";
	static const char* kChineseAnnFile = "ann_chinese.xml";
	static const char* kGrayAnnFile = "annCh.xml";

	//This is important to for key transform to chinese
	static const char* kChineseMappingFile = "province_mapping";

	typedef enum
	{
		kForward = 1, // correspond to "has plate"
		kInverse = 0  // correspond to "no plate"
	} SvmLabel;

	static const int	DEFAULT_DEBUG = 0;					// �Ƿ�Ĭ�Ͽ�������ģʽ����ʾ�м�ͼ��
	static const int	DEFAULT_WINDOW_WIDTH = 1000;		// Ĭ����ʾ���ڿ�
	static const int	DEFAULT_WINDOW_HEIGHT = 800;		// Ĭ����ʾ���ڸ�
	static const int	HORIZONTAL = 1;						// ��ȡͼ��ˮƽ���������ı�־
	static const int	VERTICAL = 0;						// ��ȡͼ��ֱ���������ı�־

	// ���ƶ�λ���ֳ���
	static const int	DEFAULT_GAUSSIANBLUR_SIZE = 5;		// Ĭ�ϸ�˹ģ��ģ���С
	static const int	SOBEL_DDEPTH = CV_16S;				// sobel�˲����ͼ������ݸ�ʽ
	static const int	SOBEL_SCALE = 1;					// ���㵼��ʱ��Ĭ�ϵ���������
	static const int	SOBEL_DELTA = 0;					// ���ڼ������ϵĳ�����Ĭ��Ϊ0
	static const int	SOBEL_X_WEIGHT = 1;					// Sobel X�����˲�ͼ��ĵ���Ȩ��
	static const int	SOBEL_Y_WEIGHT = 0;					// Sobel Y�����˲�ͼ��ĵ���Ȩ��
	static const int	DEFAULT_MORPH_SIZE_WIDTH = 17;		// Ĭ����̬ѧģ��Ŀ�
	static const int	DEFAULT_MORPH_SIZE_HEIGHT = 3;		// Ĭ����̬ѧģ��ĸ�

	static const int	DEFAULT_PLATE_DEPTH = CV_8UC3;		// Ĭ�ϳ���ͼ������ݸ�ʽ
	static const int	DEFAULT_PLATE_WIDTH = 136;			// Ĭ�ϳ��Ƴߴ��
	static const int	DEFAULT_PLATEHEIGHT = 36;			// Ĭ�ϳ��Ƴߴ��
	static const int	DEFAULT_VERIFY_MIN = 1;				// Ĭ�ϳ���������С���ϵ��
	static const int	DEFAULT_VERIFY_MAX = 24;			// Ĭ�ϳ�������������ϵ��
	static const int	DEFAULT_ANGLE = 60;					// Ĭ�ϵ����ڳ����жϵ���б�Ƕ�
	static const float	DEFAULT_ASPECT = 3.75f;				// Ĭ�ϵĳ��ƿ�߱�
	static const float	DEFAULT_ERROR = 0.9f;				// Ĭ�ϵĳ��ƿ�߱�ƫ����
	
	static const int	DEFAULT_JUMP_THRESHOLD = 7;			// Ĭ������������������Ծ������ֵΪ7
	static const int	DEFAULT_LIUDING_SIZE = 7;			// Ĭ��������СΪ7
	static const int	DEFAULT_MAT_WIDTH = 136;			// Ĭ�ϳ��ƿ��Ϊ136
	static const int	DEFAULT_COLORTHRESHOLD = 150;		// Ĭ����ɫ��ֵΪ150

	static const float	DEFAULT_SVM_PERCENTAGE = 0.7f;		//  

	// �ַ�ʶ�𲿷ֳ���
	static const int	CHAR_SIZE = 20;						// Ĭ���ַ�ͼ���С
	static const int	DEFAULT_CHARACTER_INPUT = 120;		// Ĭ���ַ�����ann�����ڵ���
	static const int	DEFAULT_CHARACTER_HIDDEN = 40;		// Ĭ���ַ�����ann�м��ڵ���
	static const int	DEFAULT_CHINESE_INPUT = 440;		// Ĭ�������ַ�����ann�����ڵ���
	static const int	DEFAULT_CHINESE_HIDDEN = 64;		// Ĭ�������ַ�����ann�м��ڵ���
	
	static const int	DEFAULT_CHINESE_CHAR_SIZE = 20;		// Ĭ�������ַ���СΪ20
	static const int	DEFAULT_LETTER_AND_NUM_SIZE = 10;	// Ĭ����Ļ�����ִ�СΪ10				

	static const int	LETTERS_AND_NUMS_NUMBER = 34;		// ���ֺ���ĸ�ĸ���
	static const int	CHINESE_NUMBER = 31;				// �����ַ�����
	static const int	ALL_CHARS_NUMBER = 65;				// �����ַ�����

	static const int	DEFAULT_GRAY_CHAR_WIDTH = 20;		// Ĭ�ϻҶ��ַ�ͼ����
	static const int	DEFAULT_GRAY_CHAR_HEIGHT = 32;		// Ĭ�ϻҶ��ַ�ͼ��߶�
	static const int	DEFAULT_CHAR_LBP_GRID_X = 4;		// Ĭ��BP-ann������x���
	static const int	DEFAULT_CHAR_LBP_GRID_Y = 4;		// Ĭ��BP-ann������y���
	static const int	DEFAULT_CHAR_LBP_PATTERNS = 16;		// Ĭ��BP-ann��ģʽ��

	static const int	CHARS_COUNT_IN_PLATE = 7;			// �����е��ַ�����һ��Ϊ7
	static const int	SYMBOLS_COUNT_IN_CHINESE_PLATE = 6;	// �����ĳ����еķ�����
	static const float	PLATE_MAX_SYMBOLS_COUNT = 7.5f;		// �����������ռ���ַ�����Ĭ��Լ����7.5��
	static const int	SPECIAL_CHAR_INDEX = 2;				// �����ַ���������

	// �����е��ַ�������+��ĸ+����
	static const char *charsTable[] =
	{
	  "0", "1", "2",
	  "3", "4", "5",
	  "6", "7", "8",
	  "9",
		/*  10  */
		"A", "B", "C",
		"D", "E", "F",
		"G", "H", /* {"I", "I"} */
		"J", "K", "L",
		"M", "N", /* {"O", "O"} */
		"P", "Q", "R",
		"S", "T", "U",
		"V", "W", "X",
		"Y", "Z",
		/*  24  */
		"zh_cuan" , "zh_e"    , "zh_gan"  ,
		"zh_gan1" , "zh_gui"  , "zh_gui1" ,
		"zh_hei"  , "zh_hu"   , "zh_ji"   ,
		"zh_jin"  , "zh_jing" , "zh_jl"   ,
		"zh_liao" , "zh_lu"   , "zh_meng" ,
		"zh_min"  , "zh_ning" , "zh_qing" ,
		"zh_qiong", "zh_shan" , "zh_su"   ,
		"zh_sx"   , "zh_wan"  , "zh_xiang",
		"zh_xin"  , "zh_yu"   , "zh_yu1"  ,
		"zh_yue"  , "zh_yun"  , "zh_zang" ,
		"zh_zhe"
		/*  31  */
	};

	// Disable the copy and assignment operator for this class.
#define DISABLE_ASSIGN_AND_COPY(className) \
private:\
  className& operator=(const className&); \
  className(const className&)

// Display the image.
#define SHOW_IMAGE(imgName, debug) \
  if (debug) \
  { \
    namedWindow("imgName", WINDOW_AUTOSIZE); \
    moveWindow("imgName", 500, 500); \
    imshow("imgName", imgName); \
    waitKey(0); \
    destroyWindow("imgName"); \
  }

// Load model. compatitable withe 3.0, 3.1 and 3.2
#ifdef CV_VERSION_THREE_TWO
#define LOAD_SVM_MODEL(model, path) \
    model = ml::SVM::load(path);
#define LOAD_ANN_MODEL(model, path) \
    model = ml::ANN_MLP::load(path);
#else
#define LOAD_SVM_MODEL(model, path) \
    model = ml::SVM::load<ml::SVM>(path);
#define LOAD_ANN_MODEL(model, path) \
    model = ml::ANN_MLP::load<ml::ANN_MLP>(path);
#endif

}

#endif // EASYPR_CONFIG_H_