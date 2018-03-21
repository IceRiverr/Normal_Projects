
#pragma once

//包含D3D相关的头文件
#include <d3d11.h>
#include "d3dx11.h"
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <d3dx11effect.h>
#include <effects.h>

#include "Source\BaseApp.h"


//顶点结构
struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca) {}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};
//顶点layout (加个const才能编译过，不知道为什么)
const D3D11_INPUT_ELEMENT_DESC in_layout[] =
{
	{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	{ "COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
};

const UINT numElements = ARRAYSIZE(in_layout);

//传到shader的constant buffer
struct VS_ConstantBuffer
{
	XMMATRIX WVP;
};

class CHelloApp : public CBaseApplication
{
public:
	CHelloApp();
	~CHelloApp();

	virtual void Init();

	virtual void Release();

	virtual void Update(double deltaTime);

	virtual void Render();

	void CompileEffect();
private:
	ID3D11Buffer *m_squareVertexBuffer;
	ID3D11Buffer *m_squareIndiceBuffer;
	ID3D11VertexShader *m_VS;
	ID3D11PixelShader *m_PS;
	ID3D10Blob *m_VS_buffer;
	ID3D10Blob *m_PS_buffer;
	ID3D11InputLayout *m_inputLayout;
	ID3D11Buffer *m_VS_objectBuffer;

	VS_ConstantBuffer m_VS_ConstantBuffer;

	ID3DX11Effect* m_pFX;
	ID3DX11EffectMatrixVariable* m_pfxWVPVar;
};
