#ifndef MATHDATAMODEL_H_
#define MATHDATAMODEL_H_


#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Model/MathTrainingSet.h"
#include "FormulaHandler.h"
#include <memory>
using namespace cv;
using namespace std;
class MathDataModel
{
public:
	MathDataModel(){
		key = 'x';
		formula = make_shared<string>();
		result = make_shared<double>();
		integrate_state = make_shared<int>(0);
		derivative_state = make_shared<int>(0);
		limit_state = make_shared<int>(0);
		point1 = make_shared<double>();
		point2 = make_shared<double>();
		formulaHandler = make_shared<FormulaHandler>();
	}
	virtual ~MathDataModel(){};
	void setImage(const IplImage* p);
	void Transform(); //call algorithm's function
	void LoadforCalc(); //calculator interface
	void Initialize(); //Learning
	shared_ptr<string> getFormula(){ return formula; }
	shared_ptr<double> getResult(){ return result; }
	shared_ptr<int> getState(){ return integrate_state; }
	shared_ptr<double> getSub(){ return point1; }
	shared_ptr<double> getSup(){ return point2; }
private:
    //image
	IplImage* image;
	//calculator
	shared_ptr<TrainingSet> MathTS;
	shared_ptr<string> formula;
	shared_ptr<double> result;
	shared_ptr<int> integrate_state;
	shared_ptr<int> derivative_state;
	shared_ptr<int> limit_state;
	char key;
	shared_ptr<double> point1;
	shared_ptr<double> point2;
	//pointer
	shared_ptr<FormulaHandler> formulaHandler;
	string InteProcess(string);
};

#endif
