// RenderArea.cpp : implementation file
//

#include "stdafx.h"
#include "RenderTests.h"
#include "RenderArea.h"

unsigned char *make_boxes_2(unsigned int szBox)
{
	unsigned int pitch = szBox * szBox * 4; // size of 1 Box x Num boxes x bytes per pixel
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
				pMem[1] = 0xFF; // G
				pMem[2] = 0x00; // R
				pMem[3] = 0xFF; // A
			}
			// No else since calloc already nulled all
			pMem += 4;
		}
	}

	return boxMem;
}

// RenderArea

RenderArea::RenderArea() : CButton()
{
	BOOL bUseDCRenderTarget = FALSE;
	EnableD2DSupport(TRUE, bUseDCRenderTarget);

	GetWICFactory(&pWicFactory);
}

RenderArea::~RenderArea()
{
}

void RenderArea::DoDataExchange(CDataExchange* pDX)
{
	CButton::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(RenderArea, CButton)
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &RenderArea::OnAfxDraw2D)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void RenderArea::OnPaint()
{
	CButton::OnPaint();
}

void RenderArea::DoD2D()
{
	if (!IsD2DSupportEnabled())
		return;

	CDCRenderTarget *pRenderTarget = GetDCRenderTarget();

	Invalidate();
	return;
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect, 1);
	return;
	
	bool b = pRenderTarget->IsValid();
	pRenderTarget->BeginDraw();
	DrawD2DResource(pRenderTarget);
	HRESULT hr = pRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
		return;

	return;
}

void RenderArea::DrawD2DResource(CHwndRenderTarget* pHwndRenderTarget)
{
	D2D1_COLOR_F crBack =
		CRenderTarget::COLORREF_TO_D2DCOLOR(::GetSysColor(COLOR_WINDOW));
	pHwndRenderTarget->Clear(crBack);

	CD2DSizeF sizeTrans(0.f, 105.f);
	pHwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(sizeTrans));

	CD2DEllipse ellipse(CD2DRectF(10.f, 10.f, 200.f, 100.f));
	CD2DSolidColorBrush brush(pHwndRenderTarget, ::GetSysColor(COLOR_WINDOWTEXT));
	pHwndRenderTarget->DrawEllipse(ellipse, &brush);
	CD2DPointF pointFrom(10.f, 10.f), pointTo(200.f, 100.f);
	pHwndRenderTarget->DrawLine(pointFrom, pointTo, &brush);

	pHwndRenderTarget->SetTransform(D2D1::IdentityMatrix());
}

void RenderArea::DrawD2DResource(CDCRenderTarget* pDCRenderTarget)
{
	ASSERT_VALID(pDCRenderTarget);

	D2D1_COLOR_F crBack =
		CRenderTarget::COLORREF_TO_D2DCOLOR(::GetSysColor(COLOR_WINDOW));
	pDCRenderTarget->Clear(crBack);

	CD2DSizeF sizeTrans(0.f, 105.f);
	pDCRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(sizeTrans));

	CD2DEllipse ellipse(CD2DRectF(10.f, 10.f, 200.f, 100.f));
	CD2DSolidColorBrush brush(pDCRenderTarget, ::GetSysColor(COLOR_WINDOWTEXT));
	pDCRenderTarget->DrawEllipse(ellipse, &brush);
	CD2DPointF pointFrom(10.f, 10.f), pointTo(200.f, 100.f);
	pDCRenderTarget->DrawLine(pointFrom, pointTo, &brush);

	pDCRenderTarget->SetTransform(D2D1::IdentityMatrix());

	return;
}

void RenderArea::DrawD2DBitmap(CHwndRenderTarget* pDCRenderTarget)
{
	unsigned char *boxData = make_boxes_2(10);

	CD2DBitmap cb(pDCRenderTarget, _T("pal_frame.bmp"), CD2DSizeU(720, 576));
	HRESULT hr = cb.Create(pDCRenderTarget);
	if (!cb.IsValid())
	{
		return;
	}

	D2D1_PIXEL_FORMAT a = cb.GetPixelFormat();

	CD2DRectU cr(0, 0, 100, 100);

	hr = cb.CopyFromMemory(boxData, 400, &cr);
	if (hr != S_OK)
	{
		return;
	}

	D2D1_COLOR_F color = { 1.f, 1.f, 1.f, 1.f };
	pDCRenderTarget->Clear(color);

	pDCRenderTarget->SetTransform(D2D1::IdentityMatrix());
	CD2DSizeF size = cb.GetSize();
	pDCRenderTarget->DrawBitmap(&cb, CD2DRectF(0, 0, size.width, size.height));

	free(boxData);
}

LRESULT RenderArea::OnAfxDraw2D(WPARAM wParam, LPARAM lParam)
{
	//CDCRenderTarget* pDCRenderTarget = (CDCRenderTarget*)lParam;
	//ASSERT_KINDOF(CDCRenderTarget, pDCRenderTarget);

	//CHwndRenderTarget* pRenderTarget = reinterpret_cast<CHwndRenderTarget*>(lParam);
	CHwndRenderTarget* pRenderTarget = (CHwndRenderTarget*)lParam;

	DrawD2DBitmap(pRenderTarget);

	//HRESULT hr = pDCRenderTarget->EndDraw();

	return TRUE;
}

HRESULT RenderArea::GetWICFactory(IWICImagingFactory** factory)
{
	static Microsoft::WRL::ComPtr<IWICImagingFactory> m_pWICFactory;
	HRESULT hr = S_OK;

	if (nullptr == m_pWICFactory)
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	}

	if (SUCCEEDED(hr))
	{
		factory = &m_pWICFactory;
	}

	return hr;
}