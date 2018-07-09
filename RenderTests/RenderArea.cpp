// RenderArea.cpp : implementation file
//

#include "stdafx.h"
#include "RenderTests.h"
#include "RenderArea.h"

// RenderArea

RenderArea::RenderArea() : CButton()
{
	BOOL bUseDCRenderTarget = TRUE;
	EnableD2DSupport(TRUE, bUseDCRenderTarget);
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
END_MESSAGE_MAP()


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

LRESULT RenderArea::OnAfxDraw2D(WPARAM wParam, LPARAM lParam)
{
	CDCRenderTarget* pDCRenderTarget = (CDCRenderTarget*)lParam;
	ASSERT_KINDOF(CDCRenderTarget, pDCRenderTarget);

	//CHwndRenderTarget* pRenderTarget = reinterpret_cast<CHwndRenderTarget*>(lParam);

	DrawD2DResource(pDCRenderTarget);

	HRESULT hr = pDCRenderTarget->EndDraw();

	return static_cast<LRESULT>(TRUE);
}