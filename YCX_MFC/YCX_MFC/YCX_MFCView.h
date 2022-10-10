
// YCX_MFCView.h: CYCXMFCView 类的接口
//

#pragma once
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

class CYCXMFCView : public CView
{
protected: // 仅从序列化创建
	CYCXMFCView() noexcept;
	DECLARE_DYNCREATE(CYCXMFCView)

// 特性
public:
	CYCXMFCDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CYCXMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void ShowBitmap(CDC* pDC, CString BmpName);
	CString EntName;	 //图像扩展名
	CString BmpName;     //图像文件名称
	//cv::String BmpName_cv; //opencv
	CBitmap m_bitmap;    //创建位图对象

	//添加成员函数
	bool ReadBmp();                            //用来读取bmp个手机图片
	bool SaveBmp(LPCSTR lpFileName);           //用来保存bmp格式图片

	//添加成员变量
	int	m_nWidth;		//图像实际宽度
	int	m_nHeight;		//图像实际高度
	int	m_nDrawWidth;	//图像显示宽度
	int	m_nDrawHeight;	//图像显示高度
	DWORD m_nImage;		//图像数据的字节数 只含位图
	DWORD m_nSize;      //图像文件大小
	int m_nLineByte;    //图像一行所占字节数
	int	m_nBitCount;    //图像每个像素所占位数
	int	m_nPalette;     //位图实际使用的颜色表中的颜色数

	BYTE* m_pImage;         //读入图片数据后的指针
	BITMAPFILEHEADER bfh;   //全局变量文件头
	BITMAPINFOHEADER bih;   //全局变量信息头
	RGBQUAD m_pPal;         //颜色表指针

	CBitmap m_bitmaplin;   //创建临时位图对象进行处理
	CString BmpNameLin;    //保存图像副本文件

	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnShowHd();
	afx_msg void OnShowTwo();
	afx_msg void OnLh2();
	afx_msg void OnLh4();
	afx_msg void OnLh8();
	afx_msg void OnLh16();
	afx_msg void OnLh32();
	afx_msg void OnLh64();
	afx_msg void OnCy();
	afx_msg void OnZftYt();
	afx_msg void OnTxzqGsph();
	afx_msg void OnTxzqPtph1();
	afx_msg void OnTxzqPtph2();
	afx_msg void OnTxzqZzlb();
	afx_msg void OnRhLaplacian();
	afx_msg void OnRhSobel();
	afx_msg void OnRhPrewitt();
	afx_msg void OnRhGtwb();
};

#ifndef _DEBUG  // YCX_MFCView.cpp 中的调试版本
inline CYCXMFCDoc* CYCXMFCView::GetDocument() const
   { return reinterpret_cast<CYCXMFCDoc*>(m_pDocument); }
#endif

