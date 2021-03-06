#pragma once


// RenderArea

class RenderArea : public CButton
{

public:
	RenderArea();
	virtual ~RenderArea();
	void OnPaint();
	void DoD2D();

	void DrawD2DResource(CHwndRenderTarget * pHwndRenderTarget);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
	LRESULT RenderArea::OnAfxDraw2D(WPARAM wParam, LPARAM lParam);
	HRESULT GetWICFactory(IWICImagingFactory ** factory);
	void DrawD2DResource(CDCRenderTarget* pDCRenderTarget);
	void DrawD2DBitmap(CHwndRenderTarget* pDCRenderTarget);

	IWICImagingFactory *pWicFactory;
};
