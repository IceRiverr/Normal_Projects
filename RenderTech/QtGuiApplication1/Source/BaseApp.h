#pragma once

#include <d3d11.h>
#include "d3dx11.h"
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <d3dx11effect.h>
#include <effects.h>

class CBaseApplication
{
public:
	CBaseApplication();
	virtual ~CBaseApplication();

	virtual void Init();

	virtual void Release();

	virtual void Update(double deltaTime);

	virtual void Render();

	void Resize(int width, int height);

	void InitD3D(int width, int height, HWND hWnd);

protected:
	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dDevContext;
	IDXGISwapChain *m_swapChain;
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilView *m_depthStencilView;
	ID3D11RenderTargetView *m_renderTargetView;
	ID3D11RasterizerState *m_rasterizeState;

	int m_width;
	int m_height;
};
