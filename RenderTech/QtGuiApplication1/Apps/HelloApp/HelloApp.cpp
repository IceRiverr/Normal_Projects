
#include "HelloApp.h"
#include "Source\Common.h"


//Xxnamath数学库里面的变量只能写成全局的，不要写为类成员
//二个cube的世界矩阵
XMMATRIX cube1WorldMat;
XMMATRIX cube2WorldMat;
XMMATRIX cube3WorldMat;
//物体的变换矩阵
XMMATRIX rotation;     //选中矩阵
XMMATRIX scale;        //缩放矩阵
XMMATRIX translation;  //平移矩阵
float rotAngle = 0.1f; //旋转角
float rotateSpeed = 1.0f; //旋转速度
						  //摄像机参数
XMMATRIX camView;
XMMATRIX camProjection;

XMVECTOR camPosition;
XMVECTOR camTarget;
XMVECTOR camUp;

CHelloApp::CHelloApp()
{

}

CHelloApp::~CHelloApp()
{

}

void CHelloApp::Init()
{
	HRESULT hr;

	//Compile Shaders from shader file
	hr = D3DX11CompileFromFile(L"Apps\\HelloApp\\Effects.fx", 0, 0, "VS", "vs_5_0", 0, 0, 0, &m_VS_buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Apps\\HelloApp\\Effects.fx", 0, 0, "PS", "ps_5_0", 0, 0, 0, &m_PS_buffer, 0, 0);

	//Create the Shader Objects
	hr = m_d3dDevice->CreateVertexShader(m_VS_buffer->GetBufferPointer(), m_VS_buffer->GetBufferSize(), NULL, &m_VS);
	hr = m_d3dDevice->CreatePixelShader(m_PS_buffer->GetBufferPointer(), m_PS_buffer->GetBufferSize(), NULL, &m_PS);

	//Set Vertex and Pixel Shaders
	m_d3dDevContext->VSSetShader(m_VS, 0, 0);
	m_d3dDevContext->PSSetShader(m_PS, 0, 0);

	//Create the vertex (在实际的开发中，不同的物体的顶点缓存和索引缓存都要写到对应的类中)
	Vertex v[] =
	{
		Vertex(-1.0f,-1.0f,-1.0f,1.0f,0.0f,0.0f,1.0f),
		Vertex(-1.0f,+1.0f,-1.0f,0.0f,1.0f,0.0f,1.0f),
		Vertex(+1.0f,+1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f),
		Vertex(+1.0f,-1.0f,-1.0f,1.0f,1.0f,0.0f,1.0f),
		Vertex(-1.0f,-1.0f,+1.0f,0.0f,1.0f,1.0f,1.0f),
		Vertex(-1.0f,+1.0f,+1.0f,1.0f,1.0f,1.0f,1.0f),
		Vertex(+1.0f,+1.0f,+1.0f,1.0f,0.0f,1.0f,1.0f),
		Vertex(+1.0f,-1.0f,+1.0f,1.0f,0.0f,0.0f,1.0f),
	};
	//create index 
	DWORD indices[] = {
		// front face
		0,1,2,
		0,2,3,

		// back face
		4,6,5,
		4,7,6,

		// left face
		4,5,1,
		4,1,0,

		// right face
		3,2,6,
		3,6,7,

		// top face
		1,5,6,
		1,6,2,

		// bottom face
		4,0,3,
		4,3,7
	};

	//index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 12 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	m_d3dDevice->CreateBuffer(&indexBufferDesc, &indexData, &m_squareIndiceBuffer);

	m_d3dDevContext->IASetIndexBuffer(m_squareIndiceBuffer, DXGI_FORMAT_R32_UINT, 0);

	//vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 8;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;
	hr = m_d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_squareVertexBuffer);

	//Set the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_d3dDevContext->IASetVertexBuffers(0, 1, &m_squareVertexBuffer, &stride, &offset);
	//Create the Input Layout
	hr = m_d3dDevice->CreateInputLayout(in_layout, numElements, m_VS_buffer->GetBufferPointer(),
		m_VS_buffer->GetBufferSize(), &m_inputLayout);
	//Set the Input Layout
	m_d3dDevContext->IASetInputLayout(m_inputLayout);
	//Set Primitive Topology
	m_d3dDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_width;
	viewport.Height = m_height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	m_d3dDevContext->RSSetViewports(1, &viewport);

	//Create the buffer to send to the cbuffer in effect file
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(VS_ConstantBuffer);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = m_d3dDevice->CreateBuffer(&cbbd, NULL, &m_VS_objectBuffer);

	//Camera information
	camPosition = XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	//Set the Projection matrix
	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, (float)m_width / m_height, 1.0f, 1000.0f);

	//set the rasterization state
	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.FillMode = D3D11_FILL_WIREFRAME; //绘制方式是线框
	wfdesc.CullMode = D3D11_CULL_NONE;
	hr = m_d3dDevice->CreateRasterizerState(&wfdesc, &m_rasterizeState);

	m_d3dDevContext->RSSetState(m_rasterizeState);

	CompileEffect();
}

void CHelloApp::Release()
{
	SAFE_RELEASE(m_squareVertexBuffer);
	SAFE_RELEASE(m_squareIndiceBuffer);
	SAFE_RELEASE(m_VS);
	SAFE_RELEASE(m_PS);
	SAFE_RELEASE(m_VS_buffer);
	SAFE_RELEASE(m_PS_buffer);
	SAFE_RELEASE(m_inputLayout);
	SAFE_RELEASE(m_VS_objectBuffer);
}

void CHelloApp::Update(double deltaTime)
{
	//使物体旋转速度不依赖于fps
	rotAngle += rotateSpeed*deltaTime;
	if (rotAngle >= 6.28f)
		rotAngle = 0.0f;

	//Reset cube1World
	cube1WorldMat = XMMatrixIdentity();

	//Define cube1's world space matrix
	XMVECTOR rotaxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	rotation = XMMatrixRotationAxis(rotaxis, rotAngle);
	translation = XMMatrixTranslation(0.0f, 0.0f, 4.0f);

	//Set cube1's world space using the transformations
	cube1WorldMat = translation * rotation;  //矩阵相乘的顺序会影响实际的旋转效果

											 //Reset cube2World
	cube2WorldMat = XMMatrixIdentity();

	//Define cube2's world space matrix
	rotation = XMMatrixRotationAxis(rotaxis, -rotAngle);
	scale = XMMatrixScaling(1.3f, 1.3f, 1.3f);

	//Set cube2's world space matrix
	cube2WorldMat = rotation * scale;

	cube3WorldMat = XMMatrixTranslation(2.0f, 0.0f, 4.0f);
	cube3WorldMat *= XMMatrixScaling(2.0f, 2.0f, 2.0f);

	//set the rasterization state
	HRESULT hr;
	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	//if (isWireFrame)
		wfdesc.FillMode = D3D11_FILL_WIREFRAME; //绘制方式切换
	//else
		//wfdesc.FillMode = D3D11_FILL_SOLID;
	wfdesc.CullMode = D3D11_CULL_NONE;
	hr = m_d3dDevice->CreateRasterizerState(&wfdesc, &m_rasterizeState);

	m_d3dDevContext->RSSetState(m_rasterizeState);
}

void CHelloApp::Render()
{
	//Clear our backbuffer
	float bgColor[4] = { (0.0f,0.0f,0.0f,0.0f) };
	m_d3dDevContext->ClearRenderTargetView(m_renderTargetView, bgColor);

	//Refresh the Depth/Stencil view
	m_d3dDevContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//1
	//Set the WVP matrix and send it to the constant buffer in effect file
	XMMATRIX WVP;
	WVP = cube1WorldMat * camView * camProjection;
	m_VS_ConstantBuffer.WVP = XMMatrixTranspose(WVP);
	m_d3dDevContext->UpdateSubresource(m_VS_objectBuffer, 0, NULL, &m_VS_ConstantBuffer, 0, 0);
	m_d3dDevContext->VSSetConstantBuffers(0, 1, &m_VS_objectBuffer);

	//Draw the first cube
	m_d3dDevContext->DrawIndexed(36, 0, 0);

	//2
	WVP = cube2WorldMat * camView * camProjection;
	m_VS_ConstantBuffer.WVP = XMMatrixTranspose(WVP);
	m_d3dDevContext->UpdateSubresource(m_VS_objectBuffer, 0, NULL, &m_VS_ConstantBuffer, 0, 0);
	m_d3dDevContext->VSSetConstantBuffers(0, 1, &m_VS_objectBuffer);

	//Draw the second cube
	m_d3dDevContext->DrawIndexed(36, 0, 0);

	// Effect
	XMMATRIX cube3MVP = cube3WorldMat * camView * camProjection;
	m_pfxWVPVar->SetMatrix((float*)&cube3MVP);
	ID3DX11EffectTechnique* mTech = m_pFX->GetTechniqueByName("ColorTech");
	D3DX11_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0, m_d3dDevContext);
		m_d3dDevContext->DrawIndexed(36, 0, 0);
	}

	//Present the backbuffer to the screen
	m_swapChain->Present(0, 0);
}

void CHelloApp::CompileEffect()
{
	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)    
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif 
	ID3D10Blob * compiledShader = 0;
	ID3D10Blob * compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(L"Apps\\HelloApp\\Effects.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, 0, &compiledShader, &compilationMsgs, 0);
	//  compilationMsgs包含错误或警告的信息
	if (compilationMsgs != 0)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		SAFE_RELEASE(compiledShader);
	}

	// 就算没有compilationMsgs，也需要确保没有其他错误
	if (FAILED(hr))
	{
		//DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11Compile FromFile", true);
	}
	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, m_d3dDevice, &m_pFX);
	// 编译完成释放资源
	SAFE_RELEASE(compiledShader);

	m_pfxWVPVar = m_pFX->GetVariableByName("WVP")->AsMatrix();
}

