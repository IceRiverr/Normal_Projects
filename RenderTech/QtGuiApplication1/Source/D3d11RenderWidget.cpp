#include <QKeyEvent>
#include "D3d11RenderWidget.h"
#include <xnamath.h>

//fps��ص�ȫ�ֱ���
double countsPerSecond = 0.0;
__int64 CounterStart = 0;

int frameCount = 0;
int fps = 0;

__int64 frameTimeOld = 0;
double frameTime;

bool isWireFrame = true; //�Ƿ��߿���Ⱦģʽ

D3d11RenderWidget::D3d11RenderWidget(QWidget *parent)
	: QWidget(parent)
	, m_App(nullptr)
{
	//���ô������ԣ��ؼ����裬����D3D���Ƴ�����
	setAttribute(Qt::WA_PaintOnScreen,true);
	setAttribute(Qt::WA_NativeWindow,true);

	m_App = new CHelloApp();
	m_App->InitD3D(800, 600, (HWND)winId());
	m_App->Init();
}

D3d11RenderWidget::~D3d11RenderWidget()
{
	m_App->Release();
}

//fps��غ���
void startFPStimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond=double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart=frequencyCount.QuadPart;
}

double getTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart-CounterStart)/countsPerSecond;
}

//��ȡÿ֡���ʱ��
double getFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount=currentTime.QuadPart-frameTimeOld;
	frameTimeOld=currentTime.QuadPart;

	if(tickCount < 0.0f)
		tickCount=0.0f;

	return float(tickCount)/countsPerSecond;
}

void D3d11RenderWidget::paintEvent(QPaintEvent *event)
{
	//����fps
	frameCount++;
	if(getTime() > 1.0f)
	{
		fps=frameCount;
		frameCount=0;
		startFPStimer();
		//���ø����ڱ�����ʾfpsֵ
		parentWidget()->setWindowTitle("FPS: "+QString::number(fps));
	}
	frameTime=getFrameTime();

	m_App->Update(frameTime);
	m_App->Render();

	update();
}

void D3d11RenderWidget::resizeEvent(QResizeEvent *event)
{
	m_App->Resize(width(), height());

}

//�����¼������ڳ������ε���
void D3d11RenderWidget::keyPressEvent(QKeyEvent *event)
{
	//�Ӵ��ڱ����ý�����ܲ�������¼���������setFocus��clearFocus��ú�ȡ������
	
}

void D3d11RenderWidget::keyReleaseEvent(QKeyEvent *event)
{

}

//���͹����¼������ڳ�����ק���Ӿ�����
void D3d11RenderWidget::mousePressEvent(QMouseEvent *event)
{
	int key=event->button();
	if(key==Qt::LeftButton)
		isWireFrame=true;
	else
		isWireFrame=false;
}

void D3d11RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void D3d11RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
	
}

void D3d11RenderWidget::wheelEvent(QWheelEvent *event)
{
	int delta=event->delta();
	if(delta>0)
		isWireFrame=true;
	else
		isWireFrame=false;
}
