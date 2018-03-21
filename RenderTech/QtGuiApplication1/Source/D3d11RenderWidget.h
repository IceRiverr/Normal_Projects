/*
//D3D��Ⱦ��Widget
//û�мӸ��ְ�ȫ������䣬Ϊ�˴���ļ��
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
	//��д�麯��
	virtual void resizeEvent(QResizeEvent *event); //�����ڳߴ�ı�ʱ��Ӧ
	virtual void paintEvent(QPaintEvent *event);   //���ڻ��ƺ���������render��ά����
	//���̺�������
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
