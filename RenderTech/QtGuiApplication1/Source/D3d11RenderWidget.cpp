#include <QKeyEvent>
#include "D3d11RenderWidget.h"
#include <xnamath.h>

//fps相关的全局变量
double countsPerSecond = 0.0;
__int64 CounterStart = 0;

int frameCount = 0;
int fps = 0;

__int64 frameTimeOld = 0;
double frameTime;

bool isWireFrame = true; //是否线框渲染模式

D3d11RenderWidget::D3d11RenderWidget(QWidget *parent)
	: QWidget(parent)
	, m_App(nullptr)
{
	//设置窗口属性，关键步骤，否则D3D绘制出问题
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

//fps相关函数
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

//获取每帧间隔时间
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
	//计算fps
	frameCount++;
	if(getTime() > 1.0f)
	{
		fps=frameCount;
		frameCount=0;
		startFPStimer();
		//设置父窗口标题显示fps值
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

//键盘事件可用于场景漫游导航
void D3d11RenderWidget::keyPressEvent(QKeyEvent *event)
{
	//子窗口必须获得焦点才能捕获键盘事件，可以用setFocus和clearFocus获得和取消焦点
	
}

void D3d11RenderWidget::keyReleaseEvent(QKeyEvent *event)
{

}

//鼠标和滚轮事件可用于场景拖拽和视距缩放
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
