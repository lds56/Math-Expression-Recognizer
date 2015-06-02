#ifndef MATHVIEWMODEL_H_
#define MATHVIEWMODEL_H_

#include "Common\BaseNotification.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <memory>
#include <string>
#include <QtWidgets>

using namespace std;

class MathDataModel;
class MathViewModel
{
public:
	MathViewModel(shared_ptr<MathDataModel> p1,shared_ptr<BaseNotification> p2,shared_ptr<string> p3,
		shared_ptr<double> p4, shared_ptr<double> p5,shared_ptr<double> p6, shared_ptr<int> p7 )
		:sp_DataModel(p1),sp_Notification(p2),formula(p3),result(p4),sub(p5),sup(p6),state(p7){}
	virtual ~MathViewModel(){}
	void LoadImage(IplImage* I);
	void startTransform();
	void startCalculate();
	void startInitialize();
	shared_ptr<string> getFormula(){return formula;}
	shared_ptr<double> getResult(){return result;}
	shared_ptr<double> getSub(){ return sub; }
	shared_ptr<double> getSup(){ return sup; }
	shared_ptr<int> getState(){ return state; }
private:
	shared_ptr<string> formula;
	shared_ptr<double> result;
	shared_ptr<double> sup;
	shared_ptr<double> sub;
	shared_ptr<int> state;
	shared_ptr<BaseNotification> sp_Notification;
	shared_ptr<MathDataModel> sp_DataModel;
};

#endif
