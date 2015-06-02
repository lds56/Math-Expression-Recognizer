#ifndef COMMAND_H_
#define COMMAND_H_

#include "Common\BaseCommand.h"
#include "ViewModel\MathViewModel.h"
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtWidgets>
using namespace std;

class InitCommand:public BaseCommand
{
public:
	InitCommand(const shared_ptr<MathViewModel>& p) :sp_ViewModel(p){}
	virtual ~InitCommand(){}
	virtual void execute()
	{
		sp_ViewModel->startInitialize();
	}
	virtual void execute(IplImage* I){}
private:
	shared_ptr<MathViewModel> sp_ViewModel;
};

class LoadCommand:public BaseCommand //button for load image
{
public:
	LoadCommand(const shared_ptr<MathViewModel>& p):sp_ViewModel(p){}
	virtual ~LoadCommand(){}
	virtual void execute(IplImage* I)
	{
		sp_ViewModel->LoadImage(I);
	}
	virtual void execute(){}
private:
	shared_ptr<MathViewModel> sp_ViewModel;
};


class RecogCommand:public BaseCommand //button for recognition
{
public:
	RecogCommand(const shared_ptr<MathViewModel>& p):sp_ViewModel(p){}
	virtual ~RecogCommand(){}
	virtual void execute()
	{
		sp_ViewModel->startTransform();
	}
	virtual void execute(IplImage* image){}
private:
	shared_ptr<MathViewModel> sp_ViewModel;
};

class CalcCommand :public BaseCommand //button for calculate
{
public:
	CalcCommand(const shared_ptr<MathViewModel>& p) :sp_ViewModel(p){}
	virtual ~CalcCommand(){}
	virtual void execute()
	{
		sp_ViewModel->startCalculate();
	}
	virtual void execute(IplImage *image){}
private:
	shared_ptr<MathViewModel> sp_ViewModel;
};

#endif
