#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <Windows.h>
#include "MathExpression.h"
#include "MathVPartition.h"
#include "MathHPartition.h"
#include "MathBPartition.h"
#include "MathTrainingSet.h"
#include "FormulaHandler.h"
using namespace std;
using namespace cv;

string FormulaHandler::transform(IplImage* image, shared_ptr<TrainingSet> MathTS)
{
	Mat aPic(image, true);
	Expression::aTrainingSetPtr = MathTS;
	Expression aPicExpr(aPic, aaa);
	return RecursiveRecog(aPicExpr).getValue();
}