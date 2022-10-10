#pragma once


// CImageZFTDlg 对话框

class CImageZFTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageZFTDlg)

public:
	CImageZFTDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImageZFTDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ZFT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_blueBZC;
	CString m_greenBZC;
	CString m_redBZC;
	CString m_bluePJHD;
	CString m_greenPJHD;
	CString m_redPJHD;
	CString m_blueXS;
	CString m_greenXS;
	CString m_redXS;
	CString m_blueZZHD;
	CString m_greenZZHD;
	CString m_redZZHD;
	afx_msg void OnPaint();
	afx_msg void OnStnClickedStaticKjGreen();
};
