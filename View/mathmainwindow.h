#ifndef MATHMAINWINDOW_H
#define MATHMAINWINDOW_H

#include "Common\BaseCommand.h"
#include "draw.h"
#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <memory>
using namespace std;

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
QT_BEGIN_NAMESPACE

class formulaLine : public QLineEdit
{
public:
	formulaLine(shared_ptr<string> p) :formula(p){}
	void setFormula() { setText(QString::fromStdString(*formula)); }
	void getFormula() { *formula = this->text().toStdString();}
private:
	shared_ptr<string> formula;
};

class resultLine : public QLineEdit
{
public:
	resultLine(shared_ptr<double> p) :result(p){}
	void setResult() { setText(QString::number(*result)); }
private:
	shared_ptr<double> result;
};

class subLine : public QLineEdit
{
public:
	subLine(shared_ptr<double> p) : subScript(p) {}
	void getSub() { *subScript = this->text().toDouble(); }
	void setSub(){ setText(QString::number(*subScript)); }
private:
	shared_ptr<double> subScript;
};

class supLine : public QLineEdit
{
public:
	supLine(shared_ptr<double> p) : supScript(p) {}
	void getSup() { *supScript = this->text().toDouble(); }
	void setSup(){ setText(QString::number(*supScript)); }
private:
	shared_ptr<double> supScript;
};

class isIntegral : public QCheckBox
{
public:
	isIntegral(shared_ptr<int> p, QString s = "Integral") : state(p), QCheckBox(s) {}
	void getState() { *state = this->checkState(); }
	int setState(){
		if (*state == 1) {
			setChecked(true);
			return 1;
		}
		else {
			setChecked(false);
			return 0;
		}
	}
private:
	shared_ptr<int> state;
};

class MathMainWindow : public QWidget
{
	Q_OBJECT

public:
	MathMainWindow(shared_ptr<int> s, shared_ptr<double> sub, shared_ptr<double> sup, shared_ptr<string> f, shared_ptr<double> r ,QWidget *parent = 0);
	void set(shared_ptr<BaseCommand> p0, shared_ptr<BaseCommand> p1, shared_ptr<BaseCommand> p2, shared_ptr<BaseCommand> p3) { c0 = p0;  c1 = p1; c2 = p2; c3 = p3; }

public slots:
	void start();
	void calculate();
	void loadFromFile();
	void submitPicture();
	void reflash(const char *p);
	void windowTransform();

private:
	QPushButton *startButton;
	QPushButton *calcButton;
	QPushButton *loadButton;
	QPushButton *submitButton;
	QPushButton *handWriteButton;
	subLine subScript;
	supLine supScript;
	isIntegral isintegral;
	formulaLine formulaline;
	resultLine resultline;
	shared_ptr<BaseCommand> c0;
	shared_ptr<BaseCommand> c1;
	shared_ptr<BaseCommand> c2;
	shared_ptr<BaseCommand> c3;
	QLabel *label = new QLabel("", 0);
	shared_ptr<draw> drawWindow;

};

#endif
