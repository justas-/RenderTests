
// RenderTestsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RenderTests.h"
#include "RenderTestsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

unsigned char *make_boxes(unsigned int szBox)
{
	unsigned int pitch = szBox * szBox * 3; // size of 1 Box x Num boxes x bytes per pixel
	unsigned int height = szBox * szBox;

	unsigned char *boxMem = (unsigned char*)calloc(pitch * height, sizeof(unsigned char));
	if (boxMem == NULL)
		return boxMem;

	unsigned char *pMem = boxMem;
	for (unsigned int row = 0; row < height; ++row)
	{
		for (unsigned int i = 0; i < szBox * szBox; ++i)
		{
			if ((i / szBox) % 2 == ((row / 10) % 2))
			{
				// 0x00 0x00 0x00 => Black
				// 0xFF 0xFF 0xFF => White
				pMem[0] = 0x00; // B
				pMem[1] = 0x00; // G
				pMem[2] = 0xFF; // R
			}
			// No else since calloc already nulled all
			pMem += 3;
		}
	}

	return boxMem;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRenderTestsDlg dialog



CRenderTestsDlg::CRenderTestsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RENDERTESTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRenderTestsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREVIEWAREA, boxPreview);
}

BEGIN_MESSAGE_MAP(CRenderTestsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTNCLR, &CRenderTestsDlg::OnBnClickedBtnclr)
	ON_BN_CLICKED(IDC_BTNRNDRES, &CRenderTestsDlg::OnBnClickedBtnrndres)
	ON_BN_CLICKED(IDC_BTNRNDFILE, &CRenderTestsDlg::OnBnClickedBtnrndfile)
	ON_BN_CLICKED(IDC_BTNRNDMEM, &CRenderTestsDlg::OnBnClickedBtnrndmem)
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CRenderTestsDlg::OnAfxDraw2D)
	ON_BN_CLICKED(IDC_BTNRNDD2D, &CRenderTestsDlg::OnBnClickedBtnrndd2d)
END_MESSAGE_MAP()


// CRenderTestsDlg message handlers
int CRenderTestsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Note: need Visual Studio 2015 or newer (_MFC_VER >= 0x0E00)
	//BOOL bUseDCRenderTarget = FALSE;
	//EnableD2DSupport(TRUE, bUseDCRenderTarget);

	//if (!IsD2DSupportEnabled())
	//	return -1;

	return 0;
}

BOOL CRenderTestsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRenderTestsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRenderTestsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Paint preview area with solid color brush
void CRenderTestsDlg::ClearPreviewArea()
{
	CRect previewRect;
	boxPreview.GetClientRect(&previewRect);
	CDC *previewDC = boxPreview.GetDC();
	previewDC->FillSolidRect(previewRect, RGB(0xaa, 0xbb, 0xcc));
	previewDC->DeleteDC();
}

void CRenderTestsDlg::DrawFromResource()
{
	CDC *previewDC, memDC;
	CBitmap bmpData, *pOldBitmap;

	if (!bmpData.LoadBitmap(IDB_BITMAP2))
		return;

	if (!(previewDC = boxPreview.GetDC()))
		return;

	if (!memDC.CreateCompatibleDC(previewDC))
		return;

	if ((pOldBitmap = memDC.SelectObject(&bmpData)) == NULL)
		return;

	if (!previewDC->BitBlt(0, 0, PALWIDTH, PALHEIGHT, &memDC, 0, 0, SRCCOPY))
		return;

	memDC.SelectObject(pOldBitmap);
	previewDC->DeleteDC();
}

void CRenderTestsDlg::DrawFromFile()
{
	CImage cim;
	CDC memDC, *previewDC;
	CBitmap *pOldBitmap;

	if (cim.Load(_T("pal_frame.bmp")) != S_OK)
		return;

	if (!(previewDC = boxPreview.GetDC()))
		return;

	if (!memDC.CreateCompatibleDC(previewDC))
		return;

	if ((pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(cim))) == NULL)
		return;

	if (!previewDC->BitBlt(0, 0, cim.GetWidth(), cim.GetHeight(), &memDC, 0, 0, SRCCOPY))
		return;

	memDC.SelectObject(pOldBitmap);
	previewDC->DeleteDC();
}

void CRenderTestsDlg::DrawFromMemory()
{
	CDC memDC, *previewDC;
	CBitmap bmpData, *pOldBitmap;
	unsigned char *pRawBitmap;
	BITMAPINFO *pBitmapInfo;

	if (!(pRawBitmap = make_boxes(10)))
		return;

	if (!(pBitmapInfo = (BITMAPINFO *)calloc(1, sizeof(BITMAPINFO))))
		goto freeraw;

	pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
	pBitmapInfo->bmiHeader.biWidth = 100;
	pBitmapInfo->bmiHeader.biHeight = 100;
	pBitmapInfo->bmiHeader.biPlanes = 1;
	pBitmapInfo->bmiHeader.biBitCount = 24;
	pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	pBitmapInfo->bmiHeader.biSizeImage = 30000; //((((src_width * 24) + 31) & ~31) >> 3) * src_height;
	pBitmapInfo->bmiHeader.biClrUsed = 0;

	if (!(previewDC = boxPreview.GetDC()))
		goto freeres;

	if (!bmpData.CreateCompatibleBitmap(previewDC, 100, 100))
		goto freeres;

	if (!memDC.CreateCompatibleDC(previewDC))
		goto freeres;

	if (!SetDIBits(previewDC->GetSafeHdc(), (HBITMAP)bmpData.GetSafeHandle(), 0, 100, pRawBitmap, pBitmapInfo, DIB_RGB_COLORS))
		goto freeres;

	if ((pOldBitmap = memDC.SelectObject(&bmpData)) == NULL)
		goto freeres;

	if (!previewDC->BitBlt(0, 0, 100, 100, &memDC, 0, 0, SRCCOPY))
		goto freeres;

	void *v = memDC.SelectObject(pOldBitmap);
	previewDC->DeleteDC();

freeres:
	free(pBitmapInfo);

freeraw:
	free(pRawBitmap);
}

void CRenderTestsDlg::DrawD2DResource(CHwndRenderTarget* pDCRenderTarget)
{
	return;
	ASSERT_VALID(pDCRenderTarget);

	D2D1_COLOR_F crBack =
		CRenderTarget::COLORREF_TO_D2DCOLOR(::GetSysColor(COLOR_WINDOW));
	pDCRenderTarget->Clear(crBack);

	//CD2DSizeF sizeTrans(0.f, 105.f);
	//pDCRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(sizeTrans));

	//CD2DEllipse ellipse(CD2DRectF(10.f, 10.f, 200.f, 100.f));
	//CD2DSolidColorBrush brush(pDCRenderTarget, ::GetSysColor(COLOR_WINDOWTEXT));
	//pDCRenderTarget->DrawEllipse(ellipse, &brush);
	//CD2DPointF pointFrom(10.f, 10.f), pointTo(200.f, 100.f);
	//pDCRenderTarget->DrawLine(pointFrom, pointTo, &brush);

	pDCRenderTarget->SetTransform(D2D1::IdentityMatrix());

	return;

	CD2DBitmap *m_pBitmamLogo = new CD2DBitmap(pRndrTrg, // parent render target
		IDB_BITMAP2,									// resource ID
		_T("BMP"));										// resource type

	HRESULT hr = m_pBitmamLogo->Create(pRndrTrg);

	CD2DSizeF sizeTarget = pRndrTrg->GetSize();
	CD2DSizeF sizeBitmap = m_pBitmamLogo->GetSize();
	// NOTE: this is simplified for demo purpose; 
	// of course, you can calculate the destination rectangle in a more sophisticated way.
	const FLOAT left = (sizeTarget.width - sizeBitmap.width) / 2;
	const FLOAT top = (sizeTarget.height - sizeBitmap.height) / 2;
	const FLOAT right = left + sizeBitmap.width;
	const FLOAT bottom = top + sizeBitmap.height;

	pRndrTrg->DrawBitmap(m_pBitmamLogo, D2D1::RectF(left, top, right, bottom));
}

void CRenderTestsDlg::OnBnClickedBtnclr()
{
	ClearPreviewArea();
}

void CRenderTestsDlg::OnBnClickedBtnrndres()
{
	DrawFromResource();
}

void CRenderTestsDlg::OnBnClickedBtnrndfile()
{
	DrawFromFile();
}

void CRenderTestsDlg::OnBnClickedBtnrndmem()
{
	DrawFromMemory();
}

void CRenderTestsDlg::OnBnClickedBtnrndd2d()
{
	boxPreview.DoD2D();
}

LRESULT CRenderTestsDlg::OnAfxDraw2D(WPARAM wParam, LPARAM lParam)
{
	//CDCRenderTarget* pDCRenderTarget = (CDCRenderTarget*)lParam;
	//ASSERT_KINDOF(CDCRenderTarget, pDCRenderTarget);

	//CHwndRenderTarget* pRenderTarget = reinterpret_cast<CHwndRenderTarget*>(lParam);
	
	CHwndRenderTarget* pRenderTarget = (CHwndRenderTarget*)lParam;
	DrawD2DResource(pRenderTarget);
	
	//pDCRenderTarget->EndDraw();
	boxPreview.DoD2D();
	
	return static_cast<LRESULT>(TRUE);
}

