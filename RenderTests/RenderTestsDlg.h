
// RenderTestsDlg.h : header file
//

#pragma once

#define PALWIDTH 720
#define PALHEIGHT 576

// CRenderTestsDlg dialog
class CRenderTestsDlg : public CDialogEx
{
// Construction
public:
	CRenderTestsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDERTESTS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	void ClearPreviewArea();
	void DrawFromResource();
	void DrawFromFile();
	void DrawFromMemory();

public:
	afx_msg void OnBnClickedBtnclr();
	afx_msg void OnBnClickedBtnrndres();
	afx_msg void OnBnClickedBtnrndfile();
	afx_msg void OnBnClickedBtnrndmem();
	CButton boxPreview;
};
