#include "QtGuiApplication1.h"
#include "Source\d3d11renderwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);

	D3d11RenderWidget *widget = new D3d11RenderWidget(this);
	widget->setMinimumSize(800, 600);
	setCentralWidget(widget);

	QPushButton* btn = new QPushButton("Test", widget);

	QPushButton* btn1 = new QPushButton("Test1", widget);
	btn1->setGeometry(100, 0, 100, 24);

	/*QLabel* name = new QLabel("Box", widget);
	btn1->setGeometry(200, 0, 100, 100);*/

	QLineEdit* input = new QLineEdit("input", widget);
	input->setGeometry(0, 36, 100, 24);
}
