
#include "BaseApp.h"
#include "Common.h"

CBaseApplication::CBaseApplication()
	: m_d3dDevice(nullptr)
	, m_d3dDevContext(nullptr)
	, m_swapChain(nullptr)
	, m_depthStencilBuffer(nullptr)
	, m_depthStencilView(nullptr)
	, m_renderTargetView(nullptr)
	, m_rasterizeState(nullptr)
{

}

CBaseApplication::~CBaseApplication()
{

}

void CBaseApplication::Init()
{

}


void CBaseApplication::Release()
{
	
	SAFE_RELEASE(m_d3dDevice);
	SAFE_RELEASE(m_d3dDevContext);
	SAFE_RELEASE(m_swapChain);
	SAFE_RELEASE(m_depthStencilBuffer);
	SAFE_RELEASE(m_depthStencilView);
	SAFE_RELEASE(m_renderTargetView);
	SAFE_RELEASE(m_rasterizeState);
}

void CBaseApplication::Update(double deltaTime)
{

}

void CBaseApplication::Render()
{

}

void CBaseApplication::Resize(int width, int height)
{
	SAFE_RELEASE(m_renderTargetView);
	SAFE_RELEASE(m_depthStencilView);
	SAFE_RELEASE(m_depthStencilBuffer);

	m_width = width;
	m_height = height;

	HRESULT hr;
	m_swapChain->ResizeBuffers(1, m_width, m_height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	//Create our BackBuffer
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	//Create our Render Target
	hr = m_d3dDevice->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView);
	SAFE_RELEASE(backBuffer);

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_width;
	depthStencilDesc.Height = m_height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Create the Depth/Stencil View
	m_d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
	m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);

	//Set our Render Target
	m_d3dDevContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_width;
	viewport.Height = m_width;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	m_d3dDevContext->RSSetViewports(1, &viewport);
}

void CBaseApplication::InitD3D(int width, int height, HWND hWnd)
{
	m_width = width;
	m_height = height;

	HRESULT hr;
	//Describe our Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = m_width;
	bufferDesc.Height = m_height;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Describe our SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	//Create our SwapChain
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_d3dDevice, NULL, &m_d3dDevContext);

	//Create our BackBuffer
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	//Create our Render Target
	hr = m_d3dDevice->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView);
	SAFE_RELEASE(backBuffer);

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_width;
	depthStencilDesc.Height = m_height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Create the Depth/Stencil View
	m_d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
	m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);

	//Set our Render Target
	m_d3dDevContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
}
