#include "draw.h"
#include "GeneratedFiles/ui_draw.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

draw::draw(QWidget *parent) :
QWidget(parent),
ui(new Ui::draw)
{
	ui->setupUi(this);
	drawing = false;
	pix = QPixmap(500, 500);
	pix.fill(Qt::white);
	label = new QLabel(this);
	label->setPixmap(pix);
	connect(this, SIGNAL(quit()), this, SLOT(load()));
}

draw::~draw()
{
	delete ui;
}

void draw::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		startPoint = event->pos();
		drawing = true;
	}
}

void draw::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && drawing)
	{
		path.moveTo(startPoint);
		path.lineTo(event->pos());
		startPoint = event->pos();
	}
	this->update();
}

void draw::mouseReleaseEvent(QMouseEvent *event)
{
	drawing = false;
	this->update();
}

void draw::paintEvent(QPaintEvent *event)
{
	QPainter painter(&pix);
	QPen pen(Qt::black, 5);
	painter.setPen(pen);
	painter.drawPath(path);
	label->setPixmap(pix);
	pix.save("Resources/handWrite.jpg");
	painter.end();
}

void draw::load()
{
	IplImage *image;
	image = cvLoadImage("Resources/handWrite.jpg");

}