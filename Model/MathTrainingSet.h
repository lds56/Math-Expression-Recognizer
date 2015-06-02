#ifndef MATHTRAININGSET_H_
#define MATHTRAININGSET_H_
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

class TrainingSet{
public:
	TrainingSet();
	void init();
	void train(const Mat& trainData, const Mat& labelData);
	int predict(const Mat& unknownData);
	char getClassValue(int i) {
		return ClassValue[i];
	}
	Mat getTrainData();
	Mat getLabelData();
	Mat getUnknownData(int grp, int cls);
	//string recog();
private:
	int nSamples;
	int nDims;
	int nClasses;
	int nTest;
	char*  ClassValue;// = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '-', '+', '/', '(', ')'};
	//enum ElementClass {0, 1, 2, 3};//, 4, "5", "6", "7", "8", "9", "+", "-", "*", "/"};
	//Mat trainData;
	//Mat labelData;
	CvANN_MLP neuralNetwork;
	CvANN_MLP_TrainParams trainParams;
};


#endif

