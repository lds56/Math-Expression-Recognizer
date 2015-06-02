#include "mathmainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtWidgets>
#include <QtWidgets/QApplication>

MathMainWindow::MathMainWindow(shared_ptr<int> s, shared_ptr<double> sub, shared_ptr<double> sup, shared_ptr<string> f, shared_ptr<double> r, QWidget *parent)
: QWidget(parent), formulaline(f), resultline(r), subScript(sub), supScript(sup), isintegral(s)
{
	drawWindow = make_shared<draw>();
    QLabel *formulaLabel = new QLabel(tr("Formula:"));

    QLabel *resultLabel = new QLabel(tr("Result:"));
    resultline.setReadOnly(true);

	QLabel *subLabel = new QLabel(tr("sub:"));
	QLabel *supLabel = new QLabel(tr("sup:"));

	handWriteButton = new QPushButton(tr("&HandWrite"));
	startButton = new QPushButton(tr("&Start"));
	calcButton = new QPushButton(tr("&Calculate"));
    loadButton = new QPushButton(tr("&Load..."));
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->setEnabled(false);

	calcButton->setToolTip(tr("Calculate the result of the formula you input"));
    loadButton->setToolTip(tr("Load a picture from a file"));
	

	connect(handWriteButton, SIGNAL(clicked()), this, SLOT(windowTransform()));
	connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
	connect(calcButton, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitPicture()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(startButton);
	buttonLayout->addWidget(calcButton);
    buttonLayout->addWidget(loadButton);
    //buttonLayout->addWidget(submitButton);
	buttonLayout->addWidget(handWriteButton);
    buttonLayout->addStretch(1);

	QHBoxLayout *integralLayout = new QHBoxLayout;
	integralLayout->addWidget(subLabel);
	integralLayout->addWidget(&subScript);
	integralLayout->addWidget(supLabel);
	integralLayout->addWidget(&supScript);
	integralLayout->addStretch(1);

	QHBoxLayout *resultLayout = new QHBoxLayout;
	resultLayout->addWidget(&resultline);
	resultLayout->addWidget(submitButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(formulaLabel, 0, 0);
    mainLayout->addWidget(&formulaline, 0, 1);
	mainLayout->addWidget(&isintegral, 1, 0);
	mainLayout->addLayout(integralLayout, 1, 1);
    mainLayout->addWidget(resultLabel, 2, 0);
	mainLayout->addLayout(resultLayout, 2, 1);
	mainLayout->addWidget(label, 0, 2, 4, 1);
	//mainLayout->addWidget(startButton, 3, 0);
    mainLayout->addLayout(buttonLayout, 3, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("Math formula recognition"));

	QPixmap mp;
	mp.load("Resources/logo.jpg");;
	label->setPixmap(mp.scaledToHeight(150));
}

void MathMainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open a picture"), "",
        tr("All picture files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

		IplImage *image;
		const QByteArray text = fileName.toLocal8Bit();
		const char *data = text.data();
		image = cvLoadImage(data);
		c1->execute(image);

		QPixmap mp;
		mp.load(fileName);;
		label->setPixmap(mp.scaledToHeight(150));
		submitButton->setEnabled(true);
    }
}

void MathMainWindow::reflash(const char *p)
{
	if (strcmp(p, "FORMULA") == 0)
	{
		formulaline.setFormula();

	}
	if (strcmp(p, "RESULT") == 0)
		resultline.setResult();

}

void MathMainWindow::submitPicture()
{
	c2->execute();
	if (isintegral.setState())
	{
		subScript.setSub();
		supScript.setSup();
	}
	else
	{
		subScript.clear();
		supScript.clear();
	}
	submitButton->setEnabled(false);
}

void MathMainWindow::calculate()
{
	formulaline.getFormula();
	subScript.getSub();
	supScript.getSup();
	isintegral.getState();
	c3->execute();
}

void MathMainWindow::start()
{
	c0->execute();
}

void MathMainWindow::windowTransform()
{
	drawWindow = make_shared<draw>();
	(*drawWindow).show();
	

	//QString fileName = "H:/cpp_pro/MathApplication/Math/Resources/handWrite.jpg";//Â·¾¶ÐÞ¸Ä
	//const QByteArray text = fileName.toLocal8Bit();
	//const char *data = text.data();
	/*IplImage *image;
	image = cvLoadImage("Resources/handWrite.jpg");
	c1->execute(image);

	QPixmap mp;
	mp.load("Resources/handWrite.jpg");;
	label->setPixmap(mp.scaledToHeight(50));

	submitButton->setEnabled(true);*/
}
