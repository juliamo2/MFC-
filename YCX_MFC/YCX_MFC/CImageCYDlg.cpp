// CImageCYDlg.cpp: 实现文件
//

#include "pch.h"
#include "YCX_MFC.h"
#include "CImageCYDlg.h"
#include "afxdialogex.h"


// CImageCYDlg 对话框

IMPLEMENT_DYNAMIC(CImageCYDlg, CDialogEx)

CImageCYDlg::CImageCYDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_xPlace(0)
	, m_yPlace(0)
{

}

CImageCYDlg::~CImageCYDlg()
{
}

void CImageCYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CYX, m_xPlace);
	DDX_Text(pDX, IDC_EDIT_CYY, m_yPlace);
}


BEGIN_MESSAGE_MAP(CImageCYDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageCYDlg 消息处理程序
