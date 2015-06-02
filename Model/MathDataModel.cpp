#include "MathDataModel.h"
#include "MathCalculator.h"
#include "Model\FormulaHandler.h"
#include <QtWidgets>

void MathDataModel::Initialize()
{
	MathTS = make_shared<TrainingSet>();
	cout << "MathPtr: " << (int)&(*(MathTS)) << endl;
	MathTS->init();
	Mat trainData(0, 0, CV_32FC1), labelData(0, 0, CV_32FC1);
	MathTS->getTrainData().convertTo(trainData, CV_32FC1);
	MathTS->getLabelData().convertTo(labelData, CV_32FC1);
	MathTS->train(trainData, labelData);
	/*cout << "done!" << endl;
	int correct = 0;
	for (int i = 1; i <= nTest; i++)
	for (int j = 0; j<16; j++) {
		Mat unknownData = MathTS->getUnknownData(i, j);
		int f = MathTS->predict(unknownData);
		cout << f << "and" << j << endl;
		cout << "--------------" << endl;
		if (f == j) correct++;
	}
	cout << "Correct Rate:" << (100 * correct) / (float)(nTest*16) << "%" << endl;
	*/
}

void MathDataModel::LoadforCalc()
{
	*result=preload(*formula, *integrate_state, *derivative_state,  *limit_state, *point1, *point2, key);
}

void MathDataModel::setImage(const IplImage* p)
{
	image= new IplImage(*p);
	
}

string MathDataModel::InteProcess(string p)
{
	double tmp1 = 0, tmp2 = 0;
	string result;
	int tmp1_point = 0, tmp2_point = 0;
	int i;
	i = p.length() - 1;
	if (p[i] != 'x' || p[i - 1] != 'd')
	{
		*integrate_state = 0;
		return p;
	}
	*integrate_state = 1;
	i = 0;
	while (p[i] != '(')
		i++;
	while (p[++i] != '(')
	{
		if (p[i] == '.')
			tmp1_point = 1;
		else if (tmp1_point == 0)
			tmp1 = tmp1 * 10 + p[i] - '0';
		else
		{
			tmp1 = tmp1 + (p[i] - '0') / pow((double)10, (double)tmp1_point);
			tmp1_point++;
		}
	}
	*point1 = tmp1;
	while (p[i] != ')')
		i++;
	while (p[++i] != ')')
	{
		if (p[i] == '.')
			tmp2_point = 1;
		else if (tmp2_point == 0)
			tmp2 = tmp2 * 10 + p[i] - '0';
		else
		{
			tmp2 = tmp2 + (p[i] - '0') / pow((double)10, (double)tmp2_point);
			tmp2_point++;
		}
	}
	i++;
	*point2 = tmp2;
	result = p.substr(i, p.length() - i - 2);
	return result;
}

void MathDataModel::Transform()
{
  *formula = InteProcess(formulaHandler->transform(image, MathTS));
}


