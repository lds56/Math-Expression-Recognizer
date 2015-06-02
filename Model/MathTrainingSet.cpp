#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <iostream>  
#include <string>  
#include <sstream>
#include <Windows.h>
#include "MathTrainingSet.h"
using namespace std;
using namespace cv;


TrainingSet::TrainingSet(){
	ClassValue = "0123456789+-*/()Id^xcosinta.";
	nSamples = 21*28;
	nDims = 2500;
	nClasses = 28;
	nTest = 1; 
	//Mat trainDatan(nSamples, nDims, CV_32FC1);
	//Mat labelData(nSamples, nClasses, CV_32FC1);
}

void TrainingSet::init(){  //?
	//CvANN_MLP::CvANN_MLP(const Mat& layerSizes, int activateFunc = CvANN_MLP::SIGMOID_SYM, double fparam1 = 0, double fparam2 = 0);
	int x1 = nDims, x2 = nClasses + 100, x3 = nClasses + 40, x4 = nClasses;//, x5 = 10; //x4 = 2, x5 = 5; //neural network layers
	CvTermCriteria criteria;
    criteria.max_iter = 100;
    criteria.epsilon  = 0.00001f;;
    criteria.type     = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
	trainParams.train_method = CvANN_MLP_TrainParams::BACKPROP;
	trainParams.bp_dw_scale = 0.05f;
	trainParams.bp_moment_scale = 0.05f;
    trainParams.term_crit = criteria;
	Mat layerSizes = (Mat_<int>(1, 4) << x1, x2, x3, x4);
	//cout << "layer:" << layerSizes << endl;
	//Mat trainData = Mat(nSamples, nDims, CV_32FC1, inputData);

	//Mat labelData = Mat(nSamples, nClasses, CV_32FC1, outputData);
	neuralNetwork.create(layerSizes, CvANN_MLP::SIGMOID_SYM, 1, 1);
}

void TrainingSet::train(const Mat& trainData, const Mat& labelData){
	neuralNetwork.train(trainData, labelData, Mat(), Mat(), trainParams);
}

int TrainingSet::predict(const Mat& unknownData){
	//Mat unknownData(1, nDims, CV_32FC1, inputData);
	Mat predictData(1, nClasses, CV_32FC1);
	neuralNetwork.predict(unknownData, predictData);
	float maxClassValue = -1, sum = 0;
	int maxClass = -1, ImpossibleNo = 0;
	for (int i = 0; i < nClasses; i++) {
		//cout << predictData.at<float>(0, i) << " ";
		sum += predictData.at<float>(0, i);
		if (predictData.at<float>(0, i) < 0.2) ImpossibleNo++;
		if (maxClassValue < predictData.at<float>(0, i)) {
			maxClass = i;
			maxClassValue = predictData.at<float>(0, i);
		}
	}
	//cout << endl;
	//cout << "predict: " << ClassValue[maxClass] << ",,,,," << sum << endl;
	//if (ImpossibleNo == nClasses - 1) return (int)maxClass;
	//else return -1;
	return maxClass;
}

Mat TrainingSet::getTrainData(){
	Mat trainData;
	for (int cls=0; cls<nClasses; cls++) {
		for (int spl=1; spl<=nSamples/nClasses; spl++) {
			stringstream str1; str1 << cls; //class
			string strCls = str1.str();
			stringstream str2; str2 << spl; //sample
			string strSpl = str2.str();  //Transform int to string
			string imagePath("Resources/img/"+strSpl+"/test"+strCls+".jpg");
			//cout << imagePath << endl;
			Mat aSample = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
		    //test here -----------------
			//namedWindow("Lena");
		    //imshow("Lena",aSample);
		    //waitKey(1);
		    //Sleep(5000);
			//cout << aSample << endl;
			//if (cls==0 && spl ==1) cout << aSample;
			//test end -----------------------
			aSample = aSample.reshape(0, 1);
			//cout << aSample.size() << endl;
			trainData.push_back(aSample);
		}
	}
	return trainData;
}

Mat TrainingSet::getLabelData() {
	Mat labelData;
	for (int cls=0; cls<nClasses; cls++) {
		for (int spl=1; spl<=nSamples/nClasses; spl++) {
			Mat aLabel = Mat::zeros(1, nClasses, CV_32FC1);
			aLabel.at<float>(0, cls) = 1;
			labelData.push_back(aLabel);
			//cout << cls << " "<< aLabel.size() << endl;
		}
	}
	//cout << "return" << endl;
	return labelData;
}

Mat TrainingSet::getUnknownData(int grp, int cls) {
	stringstream str1; str1 << cls; //class
	string strCls = str1.str();
	stringstream str2; str2 << grp; //sample
	string strGrp = str2.str();  //Transform int to string
	string imagePath("Resources/img/test"+strGrp+"/test"+strCls+".jpg");
	Mat aExample = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
	//namedWindow("Lena");
	//imshow("Lena",aExample);
	//waitKey(1);
	//Sleep(1000);
	Mat returnData(0, 0, CV_32FC1);
	aExample = aExample.reshape(0, 1);
	aExample.convertTo(returnData, CV_32FC1);
	return returnData;
}
