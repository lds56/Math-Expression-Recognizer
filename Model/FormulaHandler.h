#ifndef FORMULAHANDLER_H
#define FORMULAHANDLER_H
#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <memory>
using namespace std;
class FormulaHandler
{
public:
	FormulaHandler(){};
	~FormulaHandler(){};
	string transform(IplImage* image, shared_ptr<TrainingSet> MathTS);
	
};

#endif