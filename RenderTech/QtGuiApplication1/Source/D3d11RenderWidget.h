/*
//D3D渲染的Widget
//没有加各种安全检测的语句，为了代码的简洁
*/

#ifndef D3D11RENDERWIDGET_H
#define D3D11RENDERWIDGET_H

#include <QWidget>

#include "Apps\HelloApp\HelloApp.h"

class D3d11RenderWidget : public QWidget
{
	Q_OBJECT

public:
	D3d11RenderWidget(QWidget *parent);
	~D3d11RenderWidget();
	virtual QPaintEngine *paintEngine() const
	{
		return NULL;
	}

private:
	//重写虚函数
	virtual void resizeEvent(QResizeEvent *event); //当窗口尺寸改变时响应
	virtual void paintEvent(QPaintEvent *event);   //窗口绘制函数，用于render三维场景
	//键盘和鼠标监听
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:

private:
	CHelloApp* m_App;
};

#endif // D3D11RENDERWIDGET_H
