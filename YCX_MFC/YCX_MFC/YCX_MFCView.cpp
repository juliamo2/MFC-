
// YCX_MFCView.cpp: CYCXMFCView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "YCX_MFC.h"
#endif

#include "YCX_MFCDoc.h"
#include "YCX_MFCView.h"
#include "CImageCYDlg.h"
#include "CImageZFTDlg.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// #include <format>
// #include<opencv2\core\core.hpp>
// #include<opencv2\highgui\highgui.hpp>
// #include<opencv2\imgproc\imgproc.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>

using namespace cv;
using namespace std;

#pragma warning(disable : 4996)
#pragma warning(disable : 4018)
#pragma warning(disable : 26495)

// CYCXMFCView

IMPLEMENT_DYNCREATE(CYCXMFCView, CView)

BEGIN_MESSAGE_MAP(CYCXMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CYCXMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CYCXMFCView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CYCXMFCView::OnFileSave)
	ON_COMMAND(ID_SHOW_HD, &CYCXMFCView::OnShowHd)
	ON_COMMAND(ID_SHOW_TWO, &CYCXMFCView::OnShowTwo)
	ON_COMMAND(ID_LH_2, &CYCXMFCView::OnLh2)
	ON_COMMAND(ID_LH_4, &CYCXMFCView::OnLh4)
	ON_COMMAND(ID_LH_8, &CYCXMFCView::OnLh8)
	ON_COMMAND(ID_LH_16, &CYCXMFCView::OnLh16)
	ON_COMMAND(ID_LH_32, &CYCXMFCView::OnLh32)
	ON_COMMAND(ID_LH_64, &CYCXMFCView::OnLh64)
	ON_COMMAND(ID_CY, &CYCXMFCView::OnCy)
	ON_COMMAND(ID_ZFT_YT, &CYCXMFCView::OnZftYt)
	ON_COMMAND(ID_TXZQ_GSPH, &CYCXMFCView::OnTxzqGsph)
	ON_COMMAND(ID_TXZQ_PTPH1, &CYCXMFCView::OnTxzqPtph1)
	ON_COMMAND(ID_TXZQ_PTPH2, &CYCXMFCView::OnTxzqPtph2)
	ON_COMMAND(ID_TXZQ_ZZLB, &CYCXMFCView::OnTxzqZzlb)
	ON_COMMAND(ID_RH_Laplacian, &CYCXMFCView::OnRhLaplacian)
	ON_COMMAND(ID_RH_Sobel, &CYCXMFCView::OnRhSobel)
	ON_COMMAND(ID_RH_prewitt, &CYCXMFCView::OnRhPrewitt)
	ON_COMMAND(ID_RH_GTWB, &CYCXMFCView::OnRhGtwb)
END_MESSAGE_MAP()

// CYCXMFCView 构造/析构

CYCXMFCView::CYCXMFCView() noexcept
{
	// TODO: 在此处添加构造代码

}

CYCXMFCView::~CYCXMFCView()
{
}

BOOL CYCXMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CYCXMFCView 绘图

void CYCXMFCView::OnDraw(CDC* pDC)
{
	CYCXMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (EntName.Compare(_T("bmp")) == 0)      //bmp格式  
	{
		ReadBmp();
		ShowBitmap(pDC, BmpName);               //显示图片  
	}
}


// CYCXMFCView 打印


void CYCXMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CYCXMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CYCXMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CYCXMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CYCXMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CYCXMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CYCXMFCView 诊断

#ifdef _DEBUG
void CYCXMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CYCXMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYCXMFCDoc* CYCXMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYCXMFCDoc)));
	return (CYCXMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CYCXMFCView 消息处理程序

// numPicture变量显示图片数量
// 0-提示错误或未打开图片 1-显示一张图片 2-显示两张图片和处理
int numPicture = 0;
// level变量显示具体的处理操作，每个处理函数中赋值该变量
// 0-显示2张图片 1-显示灰度图片 3-显示图片采样
// 2 4 8 16 32 64-不同量化等级量化图片
int level = 0;

void CYCXMFCView::ShowBitmap(CDC* pDC, CString BmpName)
{
	// TODO: 在此处添加实现代码.
	//定义bitmap指针 调用函数LoadImage装载位图
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

	if (m_bitmap.m_hObject)
	{
		m_bitmap.Detach();           //切断CWnd和窗口联系
	}
	m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联

	//边界
	CRect rect;
	GetClientRect(&rect);

	//图片显示(x,y)起始坐标
	int m_showX = 0;
	int m_showY = 0;
	int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度
	int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度

	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
		return;
	BITMAP m_bmp;                          //临时bmp图片变量
	m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中
	CBitmap* pbmpOld = NULL;
	dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

	//图片显示调用函数stretchBlt
	pDC->StretchBlt(0, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0,
		m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);

	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
	DeleteObject(&m_bitmap);               //删除内存中的位图
	dcBmp.DeleteDC();                      //删除CreateCompatibleDC得到的图片DC


	/**
	 * 面代码为后面显示第二张图片
	 */


	if (numPicture == 2) {
		//显示图片函数LoadImage
		HBITMAP m_hBitmapChange{};
		m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
		if (level == 0) //显示2张图 BmpNameLin原图
		{
			m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0,
				LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
		}
		else
			if (level == 1) //灰度图片 BmpNameLin临时图片
			{
				m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
					LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
			}
			else         //量化2
				if (level == 2)
				{
					m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
						LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
				}
				else 
					if (level == 3) //图片采样
				{
					m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
						LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
				}
				else         //量化4
					if (level == 4)
					{
						m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
							LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
					}
					else         //量化8
						if (level == 8)
						{
							m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
								LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
						}
						else         //量化16
							if (level == 16)
							{
								m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
									LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
							}
							else         //量化32
								if (level == 32)
								{
									m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
										LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
								}
								else         //量化64
									if (level == 64)
									{
										m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
											LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
									}
									else         //OnTxzqGsph
										if (level == 400)
										{
											m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
												LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
										}
										else         //OnTxzqPtph1
											if (level == 401)
											{
												m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
													LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
											}
											else         //OnTxzqPtph2
												if (level == 402)
												{
													m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
														LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
												}
												else         //OnTxzqZzlb
													if (level == 403)
													{
														m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
															LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
													}
													else         //OnRhLaplacian
														if (level == 404)
														{
															m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
																LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
														}
														else         //OnRhSobel
															if (level == 405)
															{
																m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
																	LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
															}
															else         //OnRhPrewitt
																if (level == 406)
																{
																	m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
																		LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
																}
																else         //OnRhGtwb
																	if (level == 407)
																	{
																		m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0,
																			LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
																	}
		if (m_bitmap.m_hObject) {
			m_bitmap.Detach();            //m_bitmap为创建的位图对象
		}
		m_bitmap.Attach(m_hBitmapChange);
		//定义并创建一个内存设备环境
		CDC dcBmp;
		if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
			return;
		BITMAP m_bmp;                          //临时bmp图片变量
		m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中
		CBitmap* pbmpOld = NULL;
		dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

		//如果图片太大显示大小为固定640*640 否则显示原图大小
		if (m_nDrawWidth < 650 && m_nDrawHeight < 650)
			pDC->StretchBlt(m_nWindowWidth - m_nDrawWidth, 0,
				m_nDrawWidth, m_nDrawHeight, &dcBmp, 0, 0, m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);
		else
			pDC->StretchBlt(m_nWindowWidth - 640, 0, 640, 640, &dcBmp, 0, 0,
				m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);
		//恢复临时DC的位图
		dcBmp.SelectObject(pbmpOld);
	}

}


void CYCXMFCView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	//两种格式的文件：bmp gif
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	//按下确定按钮 dlg.DoModal() 函数显示对话框  
	if (dlg.DoModal() == IDOK)
	{
		BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp  
		EntName = dlg.GetFileExt();      //获取文件扩展名
		BmpNameLin = "picture.bmp";      //临时变量名
		numPicture = 1;                  //显示一张图片
		EntName.MakeLower();             //将文件扩展名转换为一个小写字符  
		Invalidate();                    //调用该函数就会调用OnDraw重绘画图  
	}
}

//***************读取图片数据*************//
bool CYCXMFCView::ReadBmp()
{
	//图片读出存储其中的东西
	FILE* fp = fopen(BmpName, "rb");
	//Mat image = imread("D://images//Fig0320(1)(top_left).tif", 1);
	if (fp == 0)
	{
		AfxMessageBox("无法打开文件!", MB_OK, 0);
		return 0;
	}
	//读取文件头 解决BMP格式倒置的方法
	fread(&bfh.bfType, sizeof(WORD), 1, fp);
	fread(&bfh.bfSize, sizeof(DWORD), 1, fp);
	fread(&bfh.bfReserved1, sizeof(WORD), 1, fp);
	fread(&bfh.bfReserved2, sizeof(WORD), 1, fp);
	fread(&bfh.bfOffBits, sizeof(DWORD), 1, fp);
	//图像文件的总字节数
	m_nSize = bfh.bfSize;
	//判断是否是bmp格式图片
	if (bfh.bfType != 0x4d42)   //'BM'
	{
		AfxMessageBox("不是BMP格式图片!", MB_OK, 0);
		return 0;
	}
	//读取信息头
	fread(&bih.biSize, sizeof(DWORD), 1, fp);
	fread(&bih.biWidth, sizeof(LONG), 1, fp);
	fread(&bih.biHeight, sizeof(LONG), 1, fp);
	fread(&bih.biPlanes, sizeof(WORD), 1, fp);
	fread(&bih.biBitCount, sizeof(WORD), 1, fp);
	fread(&bih.biCompression, sizeof(DWORD), 1, fp);
	fread(&bih.biSizeImage, sizeof(DWORD), 1, fp);
	fread(&bih.biXPelsPerMeter, sizeof(LONG), 1, fp);
	fread(&bih.biYPelsPerMeter, sizeof(LONG), 1, fp);
	fread(&bih.biClrUsed, sizeof(DWORD), 1, fp);
	fread(&bih.biClrImportant, sizeof(DWORD), 1, fp);
	if (bih.biSize != sizeof(bih))
	{
		AfxMessageBox("本结构所占用字节数出现错误");
		return 0;
	}
	//位图压缩类型，必须是 0（不压缩） 1（BI_RLE8压缩类型）或2（BI_RLE压缩类型）之一
	if (bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox("位图被压缩!");
		return 0;
	}
	//获取图像高宽和每个像素所占位数
	m_nHeight = bih.biHeight;
	m_nWidth = bih.biWidth;
	m_nDrawHeight = bih.biHeight;
	m_nDrawWidth = bih.biWidth;
	m_nBitCount = bih.biBitCount;   //每个像素所占位数
	//计算图像每行像素所占的字节数（必须是32的倍数）
	m_nLineByte = (m_nWidth * m_nBitCount + 31) / 32 * 4;
	//图片大小 调用系统自带的文件头 BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih; 
	//否则用 BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;要 m_nImage = m_nLineByte * m_nHeight - 2;
	m_nImage = m_nLineByte * m_nHeight;
	//位图实际使用的颜色表中的颜色数 biClrUsed
	m_nPalette = 0;                       //初始化
	if (bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//申请位图空间 大小为位图大小 m_nImage
	//malloc只能申请4字节的空间 （未知）
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fp);
	fclose(fp);
	return true;
}

//****************保存文件****************//
bool CYCXMFCView::SaveBmp(LPCSTR lpFileName) //lpFileName为位图文件名
{
	//保存bmp格式图片 写图片过程 只处理24像素的图片 该图片无调色板
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(lpFileName, "wb");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	//malloc只能申请4字节的空间 （未知）
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fpo);
	fwrite(m_pImage, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	return true;
}

void CYCXMFCView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	CString filter;
	filter = "所有文件(*.bmp,*.jpg)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	//重点: 1-文件打开 0-文件保存
	CFileDialog dlg(0, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
	//按下确定按钮
	if (dlg.DoModal() == IDOK) {
		CString str;
		CString strName;
		CString filename;
		str = dlg.GetPathName();           //获取文件的路径
		filename = dlg.GetFileTitle();     //获取文件名
		int nFilterIndex = dlg.m_ofn.nFilterIndex;
		if (nFilterIndex == 2)            //当用户选择文件过滤器为".BMP"时
		{
			str = str + ".bmp";	           //自动加扩展名.bmp
			SaveBmp(str);                  //保存bmp图片 就是一个写出图片的过程 
			AfxMessageBox("图片保存成功", MB_OK, 0);
		}
	}

}


void CYCXMFCView::OnShowHd()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox("载入图片后才能灰度图片!", MB_OK, 0);
		return;
	}
	AfxMessageBox("灰度图像!", MB_OK, 0);
	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	//读取文件
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	//灰度图像
	unsigned char color;
	unsigned char red, green, blue;

	/********************************************************************/
	/* 注意：原来下面所有操作都是for( i=0; i<m_nWidth*m_nHeight; i++ )
	/* 后发现如果图片最后一行没有完整的一行数据，会出现图像变多或变少
	/* 但图像的总像素为m_nImage，如果是m_nImage/3就可以保证所有像素都有
	/********************************************************************/

	for (int i = 0; i < m_nImage / 3; i++)
	{
		fread(&red, sizeof(char), 1, fpo);
		fread(&green, sizeof(char), 1, fpo);
		fread(&blue, sizeof(char), 1, fpo);

		color = (red + green + blue) / 3;
		red = color;
		green = color;
		blue = color;

		fwrite(&red, sizeof(char), 1, fpw);
		fwrite(&green, sizeof(char), 1, fpw);
		fwrite(&blue, sizeof(char), 1, fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 1;
	Invalidate();

}


void CYCXMFCView::OnShowTwo()
{
	// TODO: 在此添加命令处理程序代码
	//如果没有导入图片直接点击双显 提示错误
	if (numPicture == 0)
	{
		AfxMessageBox("载入图片后才能显示2张图片!");
		return;
	}
	AfxMessageBox("显示两张图片!", MB_OK, 0);
	numPicture = 2;    //全局变量 显示两图
	level = 0;          //level=0双显
	Invalidate();      //调用Invalidate 每秒调用一次OnDraw画图
}


void CYCXMFCView::OnLh2()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能量化!", MB_OK, 0);
		return;
	}
	AfxMessageBox("量化等级Level=2!", MB_OK, 0);
	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	//读取文件
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	//malloc只能申请4字节的空间
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fpo);
	//等级2量化
	for (int i = 0; i < m_nImage; i++) {
		//24位的为调色板为真彩图 Red Green Blue 为3字节 
		//量化等级为2取中间值为 64 和 192
		if (m_pImage[i] < 128) {
			m_pImage[i] = 0;
		}
		else if (m_pImage[i] >= 128) {
			m_pImage[i] = 128;
		}
	}
	fwrite(m_pImage, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 2;
	Invalidate();

}


void CYCXMFCView::OnLh4()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能量化!", MB_OK, 0);
		return;
	}
	AfxMessageBox("量化等级Level=4!", MB_OK, 0);
	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fpo);
	//等级4量化
	for (int i = 0; i < m_nImage; i++) {
		if (m_pImage[i] < 64) {
			m_pImage[i] = 0;
		}
		else if ((m_pImage[i] >= 64) && (m_pImage[i] < 128)) {
			m_pImage[i] = 64;
		}
		else if ((m_pImage[i] >= 128) && (m_pImage[i] < 192)) {
			m_pImage[i] = 128;
		}
		else if (m_pImage[i] >= 192) {
			m_pImage[i] = 192;
		}
	}
	fwrite(m_pImage, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 4;
	Invalidate();
}


void CYCXMFCView::OnLh8()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能量化!", MB_OK, 0);
		return;
	}
	AfxMessageBox("量化等级Level=8!", MB_OK, 0);
	//打开临时的图片 读取文件
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	//malloc只能申请4字节的空间 （未知）
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fpo);
	//等级8量化
	for (int i = 0; i < m_nImage; i++) {
		if (m_pImage[i] < 32) {
			m_pImage[i] = 0;
		}
		else if ((m_pImage[i] >= 32) && (m_pImage[i] < 64)) {
			m_pImage[i] = 32;
		}
		else if ((m_pImage[i] >= 64) && (m_pImage[i] < 96)) {
			m_pImage[i] = 64;
		}
		else if ((m_pImage[i] >= 96) && (m_pImage[i] < 128)) {
			m_pImage[i] = 96;
		}
		else if ((m_pImage[i] >= 128) && (m_pImage[i] < 160)) {
			m_pImage[i] = 128;
		}
		else if ((m_pImage[i] >= 160) && (m_pImage[i] < 192)) {
			m_pImage[i] = 160;
		}
		else if ((m_pImage[i] >= 192) && (m_pImage[i] < 224)) {
			m_pImage[i] = 192;
		}
		else if (m_pImage[i] >= 224) {
			m_pImage[i] = 224;
		}
	}
	fwrite(m_pImage, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 8;
	Invalidate();
}


void CYCXMFCView::OnLh16()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能量化!", MB_OK, 0);
		return;
	}
	AfxMessageBox("量化等级Level=16!", MB_OK, 0);
	int i, j;
	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fpo);
	for (i = 0; i < m_nImage; i++) {
		j = 16;
		while (j <= 256)
		{
			if (m_pImage[i] < j)
			{
				if (m_pImage[i] < 16)
					m_pImage[i] = 0;
				else
					m_pImage[i] = j - 16;
				break;
			}
			else j += 16;
		}
	}
	fwrite(m_pImage, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 16;
	Invalidate();
}


void CYCXMFCView::OnLh32()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能量化!", MB_OK, 0);
		return;
	}
	AfxMessageBox("量化等级Level=32!", MB_OK, 0);
	int i, j;
	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	//读取文件
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fpo);
	//等级32化
	for (i = 0; i < m_nImage; i++)
	{
		j = 8;
		while (j <= 256)
		{
			if (m_pImage[i] < j)
			{
				if (m_pImage[i] < 8)
					m_pImage[i] = 0;
				else
					m_pImage[i] = j - 8;
				break;
			}
			else j += 8;
		}
	}
	fwrite(m_pImage, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 32;
	Invalidate();
}


void CYCXMFCView::OnLh64()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能量化!", MB_OK, 0);
		return;
	}
	AfxMessageBox("量化等级Level=64!", MB_OK, 0);
	int i, j;
	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	//读取文件
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fpo);
	//等级64量化
	for (i = 0; i < m_nImage; i++)
	{
		j = 4;
		while (j <= 256)
		{
			if (m_pImage[i] < j)
			{
				if (m_pImage[i] < 16)
					m_pImage[i] = 0;
				else
					m_pImage[i] = j - 4;
				break;
			}
			else j += 4;
		}
	}
	fwrite(m_pImage, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 64;
	Invalidate();
}


void CYCXMFCView::OnCy()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能采样!", MB_OK, 0);
		return;
	}
	CImageCYDlg dlg;     //定义采样对话框
	//显示对话框
	if (dlg.DoModal() == IDOK) {
		//采样坐标最初为图片的自身像素
		if (dlg.m_xPlace == 0 || dlg.m_yPlace == 0) {
			AfxMessageBox("输入图片像素不能为0!", MB_OK, 0);
			return;
		}
		if (dlg.m_xPlace > m_nWidth || dlg.m_yPlace > m_nHeight) {
			AfxMessageBox("图片像素不能为超过原图长宽!", MB_OK, 0);
			return;
		}
		AfxMessageBox("图片采样!", MB_OK, 0);
		//打开临时的图片 读取文件
		FILE* fpo = fopen(BmpName, "rb");
		FILE* fpw = fopen(BmpNameLin, "wb+");
		fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
		fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
		fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
		fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
		fread(m_pImage, m_nImage, 1, fpo);

		/*图片采样*/
		int numWidth, numHeight;     //图片此区间取相同的像素点
		int numSYWidth, numSYHeight; //剩余期间区域 

		/*********************************************************/
		/* 表示numWidth*numHeight为一个区域 该区域颜色相同
		/* 如 512/512=1 512/512=1 1*1为一个区域
		/* dlg.m_xPlace*dlg.m_yPlace 表示新的（x,y）坐标
		/* numSYWidth表示剩余空间 该区域统一为一个颜色
		/*********************************************************/

		numWidth = m_nWidth / dlg.m_xPlace;
		numHeight = m_nHeight / dlg.m_yPlace;
		numSYWidth = m_nWidth % dlg.m_xPlace;
		numSYHeight = m_nHeight % dlg.m_yPlace;
		int Y, X;
		int i, j, m, n;
		unsigned char red, green, blue;  //存储三种颜色

		/* 有((m_xPlace * m_yPlace)+ 剩余区域 )个小区域 */
		for (i = 0; i < dlg.m_yPlace; i++)       //高度
		{
			Y = numHeight * i;                    //获取Y坐标
			for (j = 0; j < dlg.m_yPlace; j++)   //宽度
			{
				X = numWidth * j;                 //获取X坐标
				/*获取填充颜色*/
				red = m_pImage[(X + Y * m_nWidth) * 3];
				green = m_pImage[(X + Y * m_nWidth) * 3 + 1];
				blue = m_pImage[(X + Y * m_nWidth) * 3 + 2];
				/*填出图像循环 小区域中的长宽循环*/
				for (n = 0; n < numHeight; n++)
				{
					for (m = 0; m < numWidth * 3; )
					{
						m_pImage[(X + Y * m_nWidth) * 3 + m + n * m_nWidth * 3] = red;
						m++;
						m_pImage[(X + Y * m_nWidth) * 3 + m + n * m_nWidth * 3] = green;
						m++;
						m_pImage[(X + Y * m_nWidth) * 3 + m + n * m_nWidth * 3] = blue;
						m++;
					}
				}
			}
		}
		fwrite(m_pImage, m_nImage, 1, fpw);
		fclose(fpo);
		fclose(fpw);
		numPicture = 2;
		level = 3;
		Invalidate();
	}
}

int Red[256], Green[256], Blue[256];

/**************************************************/
/* 添加直方图显示功能，并在直方图下方显示相关信息
/* 如平均灰度、中值灰度、标准差和像素总数
/* ID_ZFT_YT:直方图原图显示
/**************************************************/

void CYCXMFCView::OnZftYt()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能显示原图直方图!", MB_OK, 0);
		return;
	}
	AfxMessageBox("显示原图直方图!", MB_OK, 0);
	CImageZFTDlg dlg;

	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);

	int i, j;
	for (j = 0; j < 256; j++) { //定义数组并清零
		Red[j] = 0;
		Green[j] = 0;
		Blue[j] = 0;
	}

	//计算4个数据
	unsigned char red, green, blue;
	int IntRed, IntGreen, IntBlue;                  //强制转换
	double sumRedHD = 0, sumGreenHD = 0, sumBlueHD = 0;   //记录像素总的灰度值和
	for (i = 0; i < m_nImage / 3; i++)
	{
		fread(&red, sizeof(char), 1, fpo);
		IntRed = int(red);
		sumRedHD = sumRedHD + IntRed;
		if (IntRed >= 0 && IntRed < 256) Red[IntRed]++; //像素0-255之间

		fread(&green, sizeof(char), 1, fpo);
		IntGreen = int(green);
		sumGreenHD = sumGreenHD + IntGreen;
		if (IntGreen >= 0 && IntGreen < 256) Green[IntGreen]++;

		fread(&blue, sizeof(char), 1, fpo);
		IntBlue = int(blue);
		sumBlueHD = sumBlueHD + IntBlue;
		if (IntBlue >= 0 && IntBlue < 256) Blue[IntBlue]++;
	}
	fclose(fpo);

	//像素:int型转换为CString型 
	dlg.m_redXS.Format("%d", m_nImage);
	dlg.m_greenXS.Format("%d", m_nImage);
	dlg.m_blueXS.Format("%d", m_nImage);

	//平均灰度值:计算24位bmp图片的灰度值,我是记录RGB中的所有平均值	
	float pinRedHD, pinGreenHD, pinBlueHD;
	pinRedHD = sumRedHD * 3 / m_nImage;
	pinGreenHD = sumGreenHD * 3 / m_nImage;     //平均灰度=总灰度/总像素
	pinBlueHD = sumBlueHD * 3 / m_nImage;

	dlg.m_redPJHD.Format("%.2f", pinRedHD);
	dlg.m_greenPJHD.Format("%.2f", pinGreenHD);
	dlg.m_bluePJHD.Format("%.2f", pinBlueHD);

	/****************************************************************/
	/* 中值灰度:算法重点(黄凯大神提供)
	/* 中值灰度:所有像素中的中位数,应该所有像素排序找到中间的灰度值
	/* 算法:num[256]记录各灰度出现次数,sum+=num[i],找到sum=总像素/2
	/****************************************************************/
	int sumRedZZHD = 0, sumGreenZZHD = 0, sumBlueZZHD = 0;
	int redZZHD, greenZZHD, blueZZHD;
	for (i = 0; i < 256; i++)
	{
		sumRedZZHD = sumRedZZHD + Red[i];
		if (sumRedZZHD >= m_nImage / 6)          //m_nImage被分成3份RGB并且sum=总像素/2
		{
			redZZHD = i;
			break;
		}
	}
	for (i = 0; i < 256; i++)
	{
		sumGreenZZHD = sumGreenZZHD + Green[i];
		if (sumGreenZZHD >= m_nImage / 6)          //m_nImage被分成3份RGB并且sum=总像素/2
		{
			greenZZHD = i;
			break;
		}
	}
	for (i = 0; i < 256; i++)
	{
		sumBlueZZHD = sumBlueZZHD + Blue[i];
		if (sumBlueZZHD >= m_nImage / 6)          //m_nImage被分成3份RGB并且sum=总像素/2
		{
			blueZZHD = i;
			break;
		}
	}

	dlg.m_redZZHD.Format("%d", redZZHD);
	dlg.m_greenZZHD.Format("%d", greenZZHD);
	dlg.m_blueZZHD.Format("%d", blueZZHD);

	/******************************************************************/
	/*标准差:标准差=方差的算术平方根
	/*       方差s^2=[(x1-x)^2+(x2-x)^2+......(xn-x)^2]/n
	/* 算法:不用开m_nImage数组进行计算 用num[256]中数进行
	/* 方差=(平均灰度-i)*(平均灰度-i)*Red[i]  有Red[i]个灰度值为i的数
	/******************************************************************/
	float redBZC, greenBZC, blueBZC;       //标准差
	double redFC = 0, greenFC = 0, blueFC = 0;    //方差
	for (i = 0; i < 256; i++)
	{
		redFC = redFC + (pinRedHD - i) * (pinRedHD - i) * Red[i];   //有Red[i]个像素i
		greenFC = greenFC + (pinGreenHD - i) * (pinGreenHD - i) * Green[i];
		blueFC = blueFC + (pinBlueHD - i) * (pinBlueHD - i) * Blue[i];
	}

	redBZC = sqrt(redFC * 3 / m_nImage);
	greenBZC = sqrt(greenFC * 3 / m_nImage);
	blueBZC = sqrt(blueFC * 3 / m_nImage);

	dlg.m_redBZC.Format("%.2lf", redBZC);
	dlg.m_greenBZC.Format("%.2lf", greenBZC);
	dlg.m_blueBZC.Format("%.2lf", blueBZC);

	//重点必须添加该语句才能弹出对话框
	if (dlg.DoModal() == IDOK)
	{

	}
}


void CYCXMFCView::OnTxzqGsph()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:高斯平滑", MB_OK, 0);

	/*第一步：先定义数据模板*/
	int HWS = 3;                                //模板维数为3维
	float H[3][3] = { {1.0 / 16,2.0 / 16,1.0 / 16},    //高斯模板 系数1/16
				   {2.0 / 16,4.0 / 16,2.0 / 16},
				   {1.0 / 16,2.0 / 16,1.0 / 16} };

	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	//new和delete有效的进行动态内存的分配和释放
	unsigned char* ImageSize;
	ImageSize = new unsigned char[m_nImage];
	float red, green, blue;
	int X, Y;               //一维坐标转换为二维坐标
	int TR, TG, TB;          //记录红绿蓝坐标位置

	//图像增强:平滑 
	for (int i = 0; i < m_nImage; i = i + 3)
	{
		//原图：一维矩阵转换为二维矩阵
		X = (i / 3) % m_nWidth;    //图像在X列
		Y = (i / 3) / m_nWidth;    //图像在Y行

		//赋值为黑色,相当于清零
		red = green = blue = 0;

		//对图像进行像素求和并取平均值 HWS维数
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)      //防止越界
				{
					//模板二 进行模板平均,把该点像素分散到四周
					TR = j * m_nWidth * 3 + k * 3;
					red += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TR]);
					TG = j * m_nWidth * 3 + k * 3 + 1;
					green += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TG]);
					TB = j * m_nWidth * 3 + k * 3 + 2;
					blue += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		ImageSize[i] = (unsigned char)(red);
		ImageSize[i + 1] = (unsigned char)(green);
		ImageSize[i + 2] = (unsigned char)(blue);
	}

	fwrite(ImageSize, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 400;
	Invalidate();
}


void CYCXMFCView::OnTxzqPtph1()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:普通平滑 模板一", MB_OK, 0);

	/******************************************************************/
	/* 图想平滑的算法：
	/*   1.定义常用的四个模板,它们的维数均为3,矩阵的个数均为9个数据
	/*   2.它的思想是把一个点分散到这周围的9个点上,这样使图像更模糊
	/*   3.通过卷积计算围绕该点的矩阵像素和,计算其平均值(除9)赋值给点
	/*   4.模块不同,处理后的图像也各不相同
	/******************************************************************/

	/*第一步：先定义数据模板*/
	int HWS = 3;                                //模板维数:此四个模板均为3维的
	float H1[3][3] = { {1.0 / 10,1.0 / 10,1.0 / 10},   //模板一:系数1/10
					{1.0 / 10,2.0 / 10,1.0 / 10},
					{1.0 / 10,1.0 / 10,1.0 / 10} };

	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	//new和delete有效的进行动态内存的分配和释放
	unsigned char* ImageSize;
	ImageSize = new unsigned char[m_nImage];
	float red, green, blue;
	int X, Y;               //一维坐标转换为二维坐标
	int TR, TG, TB;          //记录红绿蓝坐标位置

	//图像增强:平滑 它要获取源图像周围9个点的矩阵乘以模板9个点的矩阵,故一维图像转二维
	for (int i = 0; i < m_nImage; i = i + 3)
	{
		//原图：一维矩阵转换为二维矩阵
		X = (i / 3) % m_nWidth;    //图像在X列
		Y = (i / 3) / m_nWidth;    //图像在Y行

		//赋值为黑色,相当于清零
		red = green = blue = 0;

		//对图像进行像素求和并取平均值 HWS维数
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)      //防止越界
				{
					//模板一 进行模板平均,把该点像素分散到四周
					TR = j * m_nWidth * 3 + k * 3;
					red += H1[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TR]);
					TG = j * m_nWidth * 3 + k * 3 + 1;
					green += H1[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TG]);
					TB = j * m_nWidth * 3 + k * 3 + 2;
					blue += H1[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		ImageSize[i] = (unsigned char)(red);
		ImageSize[i + 1] = (unsigned char)(green);
		ImageSize[i + 2] = (unsigned char)(blue);
	}

	fwrite(ImageSize, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 401;
	Invalidate();

}


void CYCXMFCView::OnTxzqPtph2()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:普通平滑 模板二", MB_OK, 0);

	/*第一步：先定义数据模板*/
	int HWS = 3;
	float H2[3][3] = { {1.0 / 8,1.0 / 8,1.0 / 8},    //模板三:系数1/8 此种情况为把点转为空心矩形
					{1.0 / 8,0.0 / 8,1.0 / 8},
					{1.0 / 8,1.0 / 8,1.0 / 8} };

	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);

	//重点:图像的每行像素都必须是4的倍数：1*1的图像为 r g b 00H   
	int num;            //记录每行多余的图像素数个数  
	int sfSize;         //补齐后的图像大小  
	if (m_nWidth * 3 % 4 != 0) {
		num = (4 - m_nWidth * 3 % 4);
		sfSize = (m_nWidth * 3 + num) * m_nHeight; //每行多number个  
	}
	else {
		num = 0;
		sfSize = m_nWidth * m_nHeight * 3;
	}

	/*更改文件头信息 定义临时文件头结构变量*/
	BITMAPFILEHEADER bfhsf;
	BITMAPINFOHEADER bihsf;
	bfhsf = bfh;
	bihsf = bih;
	bfhsf.bfSize = sfSize + 54;
	fwrite(&bfhsf, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bihsf, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	//new和delete有效的进行动态内存的分配和释放
	unsigned char* ImageSize;
	ImageSize = new unsigned char[sfSize];
	float red, green, blue;
	int X, Y;               //一维坐标转换为二维坐标
	int TR, TG, TB;          //记录红绿蓝坐标位置  
	int countWidth = 0;      //记录每行的像素个数,满行时变回0  
	int place = 0;           //建立临时坐标 记录起始坐标(0,0)平移过来的位置 

	//图像增强 平滑
	for (int i = 0; i < m_nImage; )
	{
		//原图一维矩阵转换为二维矩阵
		X = (i / 3) % m_nWidth;    //图像在X列
		Y = (i / 3) / m_nWidth;    //图像在Y行

		//赋值为黑色,相当于清零
		red = green = blue = 0;

		//对图像进行像素求和并取平均值 HWS维数
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)      //防止越界
				{
					//模板二 进行模板平均,把该点像素分散到四周
					TR = j * m_nWidth * 3 + k * 3;
					red += H2[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TR]);
					TG = j * m_nWidth * 3 + k * 3 + 1;
					green += H2[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TG]);
					TB = j * m_nWidth * 3 + k * 3 + 2;
					blue += H2[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (float)(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		//通过变量place赋值变换后的图像 i始终指向原图3的倍数 为了补0而添加place变量
		ImageSize[place] = (unsigned char)(red);
		i++; place++;
		ImageSize[place] = (unsigned char)(green);
		i++; place++;
		ImageSize[place] = (unsigned char)(blue);
		i++; place++;
		countWidth = countWidth + 3;

		if (countWidth == m_nWidth * 3)
		{
			if (num == 0)
			{
				countWidth = 0;
				place = Y * m_nWidth * 3;
			}
			else //num为补0  
			{
				for (int n = 0; n < num; n++)
				{
					ImageSize[place] = 0;
					place++;
				}
				countWidth = 0;
				place = Y * (m_nWidth * 3 + num); //重点 添加Num  
			}
		}
	}

	fwrite(ImageSize, sfSize, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 402;
	Invalidate();
}


void CYCXMFCView::OnTxzqZzlb()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:中值滤波", MB_OK, 0);

	//打开临时的图片
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	//new和delete有效的进行动态内存的分配和释放
	unsigned char* ImageSize;
	ImageSize = new unsigned char[m_nImage];
	int X, Y;               //一维坐标转换为二维坐标
	int TR, TG, TB;          //记录红绿蓝坐标位置

	//选取它为中心的周围9个点像素（注意一个点为RGB）
	int H[9] = { 0,0,0,0,0,0,0,0,0 };
	int HWS = 3;             //维数为三维

	//图像增强:平滑 它要获取源图像周围9个点的矩阵乘以模板9个点的矩阵,故一维图像转二维
	for (int i = 0; i < m_nImage; i = i + 3)
	{
		//原图：一维矩阵转换为二维矩阵
		X = (i / 3) % m_nWidth;    //图像在X列
		Y = (i / 3) / m_nWidth;    //图像在Y行

		//第一行 第一列 最后一行 最后一列 直接复制
		if (X == 0 || Y == 0 || X == m_nWidth * 3 || Y == m_nHeight)
		{
			if (i + 2 > m_nImage) break;
			ImageSize[i] = m_pImage[i];
			ImageSize[i + 1] = m_pImage[i + 1];
			ImageSize[i + 2] = m_pImage[i + 2];
			continue;
		}

		//对图像进行像素求和并取平均值 HWS维数
		int num = 0;
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)      //防止越界
				{
					//获取当前位置Red像素 k一次增加RGB三个像素 R=G=B
					TR = j * m_nWidth * 3 + k * 3;
					H[num] = m_pImage[TR];
					num++;
				}
			}
		}
		//排序获取中间值
		int temp = 0;
		for (int x = 0; x < 9; x++)
		{
			for (int y = x; y < 9; y++)
			{
				if (H[x] >= H[y])
				{
					temp = H[x];
					H[x] = H[y];
					H[y] = temp;
				}
			}
		}
		//CString str;
		//str.Format("矩阵:%d %d %d, %d %d %d, %d %d %d",H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7],H[8]);
		//AfxMessageBox(str);

		//对新图像赋值 灰度图像RGB相同
		ImageSize[i] = H[4];
		ImageSize[i + 1] = H[4];
		ImageSize[i + 2] = H[4];
	}

	fwrite(ImageSize, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 403;
	Invalidate();
}


void CYCXMFCView::OnRhLaplacian()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用拉普拉斯(Laplacian)算子!");

	//模板维数:此四个模板均为3维的
	int HWS = 3;
	int H[3][3] = { {0,-1,0},    //模板为拉普拉斯算子(中心为4的Laplacian)
				{-1,4,-1},
				{0,-1,0} };

	//读写文件
	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	//new和delete有效的进行动态内存的分配和释放
	unsigned char* ImageSize;
	ImageSize = new unsigned char[m_nImage];
	int red, green, blue;
	int X, Y;       //一维坐标转换为二维坐标
	int TR, TG, TB;  //记录红绿蓝坐标位置

	//图像增强 锐化
	for (int i = 0; i < m_nImage; i = i + 3)
	{
		X = (i / 3) % m_nWidth;    //X列
		Y = (i / 3) / m_nWidth;    //Y行
		red = green = blue = 0;

		//对图像进行像素求和并取平均值 HWS维数
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)
				{

					TR = j * m_nWidth * 3 + k * 3;
					red += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TR]);
					TG = j * m_nWidth * 3 + k * 3 + 1;
					green += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TG]);
					TB = j * m_nWidth * 3 + k * 3 + 2;
					blue += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		if (red >= 0 && red < 256) ImageSize[i] = red;
		else if (red < 0) ImageSize[i] = 0;      //ImageSize[i]=-red;
		else ImageSize[i] = 0;

		if (green >= 0 && green < 256) ImageSize[i + 1] = green;
		else if (green < 0) ImageSize[i + 1] = 0;  //ImageSize[i+1]=-green;
		else ImageSize[i + 1] = 0;

		if (blue >= 0 && blue < 256) ImageSize[i + 2] = blue;
		else if (blue < 0) ImageSize[i + 2] = 0;   //ImageSize[i+2]=-blue;
		else ImageSize[i + 2] = 0;
	}

	fwrite(ImageSize, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 404;
	Invalidate();
}


void CYCXMFCView::OnRhSobel()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用Sobel算子!");

	int HWS = 3;
	//模板为Sobel算子
	int HX[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	int HY[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };

	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	unsigned char* ImageSize;
	ImageSize = new unsigned char[m_nImage];
	int redX, greenX, blueX;
	int redY, greenY, blueY;
	int X, Y;
	int TR, TG, TB;

	//图像增强 锐化
	for (int i = 0; i < m_nImage; i = i + 3)
	{
		X = (i / 3) % m_nWidth;    //X列
		Y = (i / 3) / m_nWidth;    //Y行
		redX = greenX = blueX = 0;
		redY = greenY = blueY = 0;

		//对图像进行像素求和并取平均值 HWS维数
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)
				{

					TR = j * m_nWidth * 3 + k * 3;
					redX += HX[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TR]);
					redY += HY[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TR]);
					TG = j * m_nWidth * 3 + k * 3 + 1;
					greenX += HX[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TG]);
					greenY += HY[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TG]);
					TB = j * m_nWidth * 3 + k * 3 + 2;
					blueX += HX[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TB]);
					blueY += HY[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TB]);
				}
			}
		}
		//s=(d(x)*d(x)+d(y)*d(y))开根号
		int R, G, B;
		R = (int)(sqrt(redX * redX * 1.0 + redY * redY * 1.0));
		G = (int)(sqrt(greenX * greenX * 1.0 + greenY * greenY * 1.0));
		B = (int)(sqrt(blueX * blueX * 1.0 + blueY * blueY * 1.0));

		if (redX < 0 && redY < 0) ImageSize[i] = 0;
		else if (R > 255) ImageSize[i] = 255;
		else ImageSize[i] = R;

		if (greenX < 0 && greenY < 0) ImageSize[i + 1] = 0;
		else if (G > 255) ImageSize[i + 1] = 255;
		else ImageSize[i + 1] = G;

		if (blueX < 0 && blueY < 0) ImageSize[i + 2] = 0;
		else if (B > 255) ImageSize[i + 2] = 255;
		else ImageSize[i + 2] = B;
	}

	fwrite(ImageSize, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 405;
	Invalidate();
}


void CYCXMFCView::OnRhPrewitt()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用Prewitt算子!");

	int HWS = 3;
	int H[3][3] = { {1,0,-1},    //模板为Prewitt算子
				{1,0,-1},
				{1,0,-1} };

	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	unsigned char* ImageSize;
	ImageSize = new unsigned char[m_nImage];
	int red, green, blue;
	int X, Y;
	int TR, TG, TB;

	//图像增强:平滑
	for (int i = 0; i < m_nImage; i = i + 3)
	{
		X = (i / 3) % m_nWidth;    //X列
		Y = (i / 3) / m_nWidth;    //Y行
		red = green = blue = 0;

		//对图像进行像素求和并取平均值 HWS维数
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)
				{

					TR = j * m_nWidth * 3 + k * 3;
					red += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TR]);
					TG = j * m_nWidth * 3 + k * 3 + 1;
					green += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TG]);
					TB = j * m_nWidth * 3 + k * 3 + 2;
					blue += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		if (red >= 0 && red < 256) ImageSize[i] = red;
		else if (red < 0) ImageSize[i] = 0;      //ImageSize[i]=-red;
		else ImageSize[i] = 0;

		if (green >= 0 && green < 256) ImageSize[i + 1] = green;
		else if (green < 0) ImageSize[i + 1] = 0;  //ImageSize[i+1]=-green;
		else ImageSize[i + 1] = 0;

		if (blue >= 0 && blue < 256) ImageSize[i + 2] = blue;
		else if (blue < 0) ImageSize[i + 2] = 0;   //ImageSize[i+2]=-blue;
		else ImageSize[i + 2] = 0;
	}
	fwrite(ImageSize, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 406;
	Invalidate();
}


void CYCXMFCView::OnRhGtwb()
{
	// TODO: 在此添加命令处理程序代码
	if (numPicture == 0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!", MB_OK, 0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用高通模板!");

	int HWS = 3;
	int H[3][3] = { {-1,-1,-1},
				{-1,8,-1},
				{-1,-1,-1} };

	FILE* fpo = fopen(BmpName, "rb");
	FILE* fpw = fopen(BmpNameLin, "wb+");
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fpo);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fpo);
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fpw);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fpw);
	fread(m_pImage, m_nImage, 1, fpo);

	unsigned char* ImageSize;
	ImageSize = new unsigned char[m_nImage];
	int red, green, blue;
	int X, Y;
	int TR, TG, TB;

	//图像增强 锐化
	for (int i = 0; i < m_nImage; i = i + 3)
	{
		X = (i / 3) % m_nWidth;    //X列
		Y = (i / 3) / m_nWidth;    //Y行
		red = green = blue = 0;

		//对图像进行像素求和并取平均值 HWS维数
		for (int j = Y - HWS / 2; j < Y + HWS / 2 + 1; j++)                      //第j行
		{
			for (int k = X - HWS / 2; k < X + HWS / 2 + 1; k++)                  //第k列
			{
				if (j >= 0 && k >= 0 && k < m_nWidth && j < m_nHeight)
				{

					TR = j * m_nWidth * 3 + k * 3;
					red += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TR]);
					TG = j * m_nWidth * 3 + k * 3 + 1;
					green += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TG]);
					TB = j * m_nWidth * 3 + k * 3 + 2;
					blue += H[(j - Y + HWS / 2)][(k - X + HWS / 2)] * (m_pImage[TB]);
				}
			}
		}

		//对新图像赋值
		if (red >= 0 && red < 256) ImageSize[i] = red;
		else if (red < 0) ImageSize[i] = 0;      //ImageSize[i]=-red;
		else ImageSize[i] = 0;

		if (green >= 0 && green < 256) ImageSize[i + 1] = green;
		else if (green < 0) ImageSize[i + 1] = 0;  //ImageSize[i+1]=-green;
		else ImageSize[i + 1] = 0;

		if (blue >= 0 && blue < 256) ImageSize[i + 2] = blue;
		else if (blue < 0) ImageSize[i + 2] = 0;   //ImageSize[i+2]=-blue;
		else ImageSize[i + 2] = 0;
	}

	fwrite(ImageSize, m_nImage, 1, fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level = 407;
	Invalidate();
}
