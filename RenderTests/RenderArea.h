#pragma once


// RenderArea

class RenderArea : public CButton
{

public:
	RenderArea();
	virtual ~RenderArea();
	void DoD2D();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
	LRESULT RenderArea::OnAfxDraw2D(WPARAM wParam, LPARAM lParam);
	void DrawD2DResource(CDCRenderTarget* pDCRenderTarget);
};
