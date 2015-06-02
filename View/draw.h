#ifndef DRAW_H
#define DRAW_H

#include <QtWidgets/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QPainterPath>
#include <QtWidgets/QLabel>
#include <iostream>

namespace Ui {
	class draw;
}

class draw : public QWidget
{
	Q_OBJECT

public:
	explicit draw(QWidget *parent = 0);
	~draw();
public slots:
	void load();
protected:
	void mousePressEvent(QMouseEvent *);       //��дmousePressEvent����
	void mouseMoveEvent(QMouseEvent *);        //��дmouseMoveEvent����
	void mouseReleaseEvent(QMouseEvent *);     //��дmouseReleaseEvent����
	void paintEvent(QPaintEvent *);            //��дpaintEvent����

private:
	Ui::draw *ui;
	bool drawing;
	QPoint startPoint;
	QPainterPath path;
	QPixmap pix;
	QLabel *label;
};

#endif