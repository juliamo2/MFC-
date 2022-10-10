#pragma once


// CImageCYDlg 对话框

class CImageCYDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageCYDlg)

public:
	CImageCYDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImageCYDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_xPlace;
	int m_yPlace;
};
