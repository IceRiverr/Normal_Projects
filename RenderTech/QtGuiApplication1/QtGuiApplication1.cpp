#include "QtGuiApplication1.h"
#include "Source\d3d11renderwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	D3d11RenderWidget *widget = new D3d11RenderWidget(this);
	widget->setMinimumSize(800, 600);
	setCentralWidget(widget);
}
