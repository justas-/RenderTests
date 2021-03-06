
// RenderTestsDlg.h : header file
//

#pragma once

#include "RenderArea.h"

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

	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnAfxDraw2D(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	void ClearPreviewArea();
	void DrawFromResource();
	void DrawFromFile();
	void DrawFromMemory();
	void DrawD2DResource(CHwndRenderTarget * pDCRenderTarget);
	void DrawD2DResource(CDCRenderTarget* pDCRenderTarget);

	CHwndRenderTarget* pRndrTrg;

public:
	afx_msg void OnBnClickedBtnclr();
	afx_msg void OnBnClickedBtnrndres();
	afx_msg void OnBnClickedBtnrndfile();
	afx_msg void OnBnClickedBtnrndmem();
	
//	RenderArea boxPreview;
	afx_msg void OnBnClickedBtnrndd2d();
	RenderArea boxPreview;
};
