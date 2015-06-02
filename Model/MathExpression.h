/*
 * Expression.h
 *
 *  Created on: 2014Äê7ÔÂ11ÈÕ
 *      Author: lds
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>
#include "MathVPartition.h"
#include "MathHPartition.h"
#include "MathBPartition.h"
#include "MathTrainingSet.h"

using namespace std;
using namespace cv;

enum MethodType {Vertical, Horizontal, Block, aaa};

class Expression {
public:
	Expression(Mat aMat, MethodType method);//, CvANN_MLP* aTSPtr);  //is not simple
	Expression(bool isSimpleExpr, string value, MethodType method);//, CvANN_MLP* aTSPtr); //is simple
	bool verticalPartition();
	bool horizontalPartition(); //if success, then return TRUE
	bool blockPartition();
	int exprRecog(); // should set value
	void partition();
	string transform();
	Expression subExpressionAt(int i) {return SubExpression[i];}
	int subSize() { return SubExpression.size(); }
	bool isSimple() { return isSimpleExpr; }
	bool checkSimplity();
	string getValue() { return Value; }
	Mat getData() {return Data;}
	MethodType getMethod() { return Method; }
	static shared_ptr<TrainingSet> aTrainingSetPtr;
private:
	bool isSimpleExpr;
	string Value;  //if failed to recoganize, then set -1;
	vector<Expression> SubExpression;
	MethodType Method;  //if True, V; else H
	Mat Data; //?
	//CvANN_MLP* aTrainingSetPtr;
};

shared_ptr<TrainingSet> Expression::aTrainingSetPtr;

Expression Combine(Expression);
Mat MatNormalize(Mat);
int flag;

//string Recog(Mat aMat);
bool Expression::verticalPartition() {
	//cout << "Enter V" << endl;

	//namedWindow("v1", CV_WINDOW_AUTOSIZE);
	//imshow("v1", Data);
	//waitKey();
	//destroyWindow("v1");


	imwrite("doit.jpg", Data);
	Mat aNewMat = Data.clone();
	//IplImage anImage = aNewMat.operator _IplImage();
	IplImage* anImage = cvLoadImage("doit.jpg", 1);
	vector<IplImage*> imgVector = vPartition(anImage);
	vector<IplImage*>::iterator imgIter = imgVector.begin();

	/*namedWindow("v2", CV_WINDOW_AUTOSIZE);
	imshow("v2", Data);
	waitKey();

	destroyWindow("v2");


	namedWindow("v3", CV_WINDOW_AUTOSIZE);
	imshow("v3", aNewMat);
	waitKey();
	destroyWindow("v3");


	namedWindow("it", CV_WINDOW_AUTOSIZE);
	cvShowImage("it", *imgIter);
	waitKey();
	destroyWindow("it");*/

	cout << "size:" << imgVector.size() << endl;
	if (imgVector.size() == 1) return false;
	//cout << "size:" << imgVector.size() << endl;   ////////////////
	for (; imgIter != imgVector.end(); imgIter++) {
		Mat aMat(*imgIter, Vertical);
		//if ((ii++) == 2) flag = false;   /////////////
		//if (imgIter+1 == imgVector.end()) flag = false;

		//cout << "ii:" << ii << endl;  ////////////

		//namedWindow("sub", CV_WINDOW_AUTOSIZE);
		//imshow("sub", aMat);
		//waitKey();

		Expression aSubExpr(aMat, Vertical);
		SubExpression.push_back(aSubExpr);
	};
	//flag = true;  /////////////////
	return true;
}

bool Expression::horizontalPartition() {
	cout << "Enter H" << endl;
	//IplImage anImage = Data.operator _IplImage();
	//namedWindow("hhh", CV_WINDOW_AUTOSIZE);
	//imshow("hhh", Data);
	//waitKey();

	Mat aNewMat = Data.clone();
	IplImage anImage = aNewMat.operator _IplImage();

	vector<IplImage*> imgVector = hPartition(&anImage);
	//cout << "img:" << imgVector.size() << endl;   /////////////////
	vector<IplImage*>::iterator imgIter = imgVector.begin();
	if (imgVector.size() == 1) return false;
	for (; imgIter != imgVector.end(); imgIter++) {
		Mat aMat(*imgIter);
		Expression aSubExpr(aMat, Horizontal);
		SubExpression.push_back(aSubExpr);
	};
	//cout << "hoor:" << SubExpression.size() << endl;   ///////////////////
	return true;
}

bool Expression::blockPartition() {
	//cout << "Enter B" << endl;
	//IplImage anImage = Data.operator _IplImage();
	//namedWindow("hhh", CV_WINDOW_AUTOSIZE);
	//imshow("hhh", Data);
	//waitKey();

	Mat aNewMat = Data.clone();
	IplImage anImage = aNewMat.operator _IplImage();

	vector<IplImage*> imgVector = bPartition(&anImage);
	//cout << "img:" << imgVector.size() << endl;   /////////////////
	vector<IplImage*>::iterator imgIter = imgVector.begin();

	//namedWindow("bmage1", CV_WINDOW_AUTOSIZE);
	//cvShowImage("bmage1", *imgIter);
	//waitKey();
	//destroyWindow("bmage1");

	Mat aMat(*imgIter);
	Expression aSubExpr(aMat, Block);
	SubExpression.push_back(aSubExpr);
	//if (imgVector.size() == 1) return false;
	//for (; imgIter != imgVector.end(); imgIter++) {
	//Mat aMat(*imgIter);
	//Expression aSubExpr(aMat, Horizontal);
	//SubExpression.push_back(aSubExpr);
	//};
	//cout << "hoor:" << SubExpression.size() << endl;   ///////////////////
	return true;
}

int Expression::exprRecog() {
	Mat returnData(0, 0, CV_32FC1), aData;

	//cout << aData.type() << endl;
	//cout << aData.size() << endl;

	aData = MatNormalize(Data).clone();
	//if (aData.empty()) return -1;

	//namedWindow("Rmage", CV_WINDOW_AUTOSIZE);
	//imshow("Rmage", aData);
	//waitKey();
	//destroyWindow("Rmage");

	aData = aData.reshape(0, 1);

	//cout << aData.type() << endl;
	//cout << aData.size() << endl;

	aData.convertTo(returnData, CV_32FC1);
	//cvtColor(returnData, returnData, CV_RGB2GRAY);
	//cout << returnData.type() << endl;
	//cout << returnData.size() << endl;
	//cout << "EXPtr: "<<(int)&(*(Expression::aTrainingSetPtr)) << endl;
	int RecogResult = Expression::aTrainingSetPtr->predict(returnData);
	//cout << "Result: " << RecogResult << endl;
	//return flag;
	return RecogResult;
	//TrainingSet::predict();
	//string recogValue = "H";
	//this->Value = recogValue;
	//return flag;
}

Expression::Expression(Mat aMat, MethodType method) {
	string value;
	Data = aMat;
	Method = method;
	int RecogResult = exprRecog();
	this->Method = method;
	this->isSimpleExpr = false;
	if (checkSimplity()) {
		this->isSimpleExpr = true;
		this->Value = Expression::aTrainingSetPtr->getClassValue(RecogResult);
		//cout << "value: " << this->Value << endl;
		//this->Method = true;
	}
}

Expression::Expression(bool isSimpleExpr, string value, MethodType method) {
	this->isSimpleExpr = isSimpleExpr;
	this->Value = value;
	this->Method = method;
}

void Expression::partition() {
	cout << "Enter Parti" << endl;
	if (verticalPartition()) return;
	//this->Method = Vertical;
	else if (horizontalPartition()) return;
	else if (blockPartition()) return;
	//this->Method = Horizontal;
}

Expression RecursiveRecog(Expression aExpression) {
	//cout << "Enter Recursion" << endl;
	//cout << "Simple: " << aExpression.isSimple() << endl;
	if (aExpression.isSimple()) return aExpression;
	return Combine(aExpression);
}

bool Expression::checkSimplity() {
	//cout << "Method: " << Method << endl;
	/*if (Method == Vertical )  { //means V
	IplImage anImage = Data.operator _IplImage();
	if (hPartition(&anImage).size()>= 3) return false;
	else return true;
	cout << "Check: " << hPartition(&anImage).size() << endl;
	} else if (Method == Horizontal ) {  //means H
	IplImage anImage = Data.operator _IplImage();
	if (vPartition(&anImage).size()>= 2) return false;
	else return true;
	cout << "Check: " << vPartition(&anImage).size() << endl;
	} else if (Method == Block) {
	IplImage anImage = Data.operator _IplImage();
	if (hPartition(&anImage).size()>= 3) return false;
	if (vPartition(&anImage).size()>= 2) return false;
	return true;
	}
	else { return false; } */
	Mat Data0 = Data.clone();
	IplImage anImage = Data0.operator _IplImage();
	//namedWindow("image1", CV_WINDOW_AUTOSIZE);
	//cvShowImage("image1", &anImage);
	//waitKey();
	//destroyWindow("image1");


	//anImage = Data.clone().operator _IplImage();
	if (vPartition(&anImage).size() >= 2) return false;
	//cout << "v done" << endl;

	//namedWindow("D", CV_WINDOW_AUTOSIZE);
	//imshow("D", Data);
	//waitKey();
	//destroyWindow("D");

	Mat Data1 = Data.clone();
	IplImage anImage1 = Data1.operator _IplImage();

	//namedWindow("image2", CV_WINDOW_AUTOSIZE);
	//cvShowImage("image2", &anImage1);
	//waitKey();
	//destroyWindow("image2");

	if (hPartition(&anImage1).size() >= 3) return false;
	//cout << "h done" << endl;

	Mat Data2 = Data.clone();
	IplImage anImage2 = Data2.operator _IplImage();//c/vCreateImage(cvGetSize(&anImage), anImage.depth. anImage.nChannels);
	//cvCopy(anImage, anImage2);
	//namedWindow("image3", CV_WINDOW_AUTOSIZE);
	//cvShowImage("image3", &anImage2);
	//waitKey();
	//destroyWindow("image3");
	//cvSaveImage("save.jpg", &anImage2);
	if (bPartition(&anImage2).size() == 1) return false;
	//cout << "b done" << endl;
	return true;
}

string Expression::transform() {
	//cout << "Method and Value: " << Method << ", " << Value
		//<< endl;
	switch (Method) {
	case 0:
		return Value;
	case 1: //Horiontal
		if (Value == "-") return "/";
		else {
			bool AllNumber = true;
			for (unsigned int i = 0; i<Value.size(); i++)
			if (!('0' <= Value[i] && Value[i] <= '9'))
				AllNumber = false;
			if (AllNumber == true) return Value;
			else return "(" + Value + ")";
		}
	case 2:
		return "(" + Value + ")^0.5";
	case 3:
	default:
		return Value;
	}
}

Expression Combine(Expression aExpression) {
	string str = "";
	aExpression.partition();
	//cout << "aExpression:" << aExpression.subSize() << endl;  ///////
	//cout << "Enter Combine" << endl;

	/////////////////////////////////////////////////
	for (int i = 0; i<aExpression.subSize(); i++) {
		//string aStr = RecursiveRecog( aExpression.subExpressionAt(i) ).getValue();
		str = str + RecursiveRecog(aExpression.subExpressionAt(i)).transform();
		//namedWindow("image", CV_WINDOW_AUTOSIZE);
		//imshow("image", aExpression.subExpressionAt(i).getData());
		//waitKey();
		//destroyWindow("image");
		//cout << "simple:" << ii << "," <<

		//cout << aExpression.subExpressionAt(i).isSimple() << endl;  ////////
	}
	if (aExpression.subSize()>1 && aExpression.subExpressionAt(1).getValue() == "I")
		str = "(" + str + ")";
	//cout << "string:" << str << "Method: " << aExpression.getMethod() << endl;
	Expression simpleExpression(true, str, aExpression.getMethod());  //unknown method
	return simpleExpression;
}

Mat MatNormalize(Mat aMat) {

	//imwrite("tmp.jpg", aMat);
	//IplImage * anImagePtr = cvLoadImage("tmp.jpg", -1);
	//Mat newMat = aMat.clone();
	IplImage anImagePtr = aMat.operator _IplImage();//IplImage(newMat);
	//IplImage* im2 = cvCreateImage(cvGetSize(&anImagePtr), anImagePtr.depth, 1);
	//im2 = cvCloneImage(im);
	//cvCvtColor(&anImagePtr, im2, CV_RGB2GRAY);
	//IplImage* anNewImagePtr;
	//cvCopy(anImagePtr, anNewImagePtr);
	IplImage* anNormalizedImagePtr = normlize(&anImagePtr);
	Mat aReturnedMat(anNormalizedImagePtr, true);
	//Mat aNewReturnedMat(aReturnedMat.size(), CV_32F);
	//cout << "Type: " << CV_32FC1 << "," << aNewReturnedMat.type() << endl;
	//cout << "Channel: " << aNewReturnedMat.channels() << endl;
	//Sleep(100000);
	if (aReturnedMat.channels() == 3)
		cvtColor(aReturnedMat, aReturnedMat, CV_BGR2GRAY);
	//cout << "Type: " << CV_32FC1 << ", " << aReturnedMat.type() << endl;
	//Mat newMat = aMat.clone();
	//IplImage* anImagePtr=cvCloneImage(&(IplImage)newMat);
	//IplImage* anNormalizedImagePtr= normlize(anImagePtr);
	//Mat aReturnedMat(anNormalizedImagePtr);

	/*namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", aMat);
	waitKey();
	destroyWindow("image");

	namedWindow("image", CV_WINDOW_AUTOSIZE);
	cvShowImage("image", anImagePtr);
	waitKey();
	destroyWindow("image");

	namedWindow("image", CV_WINDOW_AUTOSIZE);
	cvShowImage("image", anNormalizedImagePtr);
	waitKey();
	destroyWindow("image");

	Sleep(10000);*/
	return aReturnedMat;
}

#endif /* EXPRESSION_H_ */
