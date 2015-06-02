#include "ViewModel\MathViewModel.h"
#include "Model\MathDataModel.h"
#include <QtWidgets>

void MathViewModel::LoadImage(IplImage* I)
{
	sp_DataModel->setImage(I);
}

void MathViewModel::startInitialize()
{
	sp_DataModel->Initialize();
}

void MathViewModel::startTransform()
{
	sp_DataModel->Transform();
	sp_Notification->trigger("FORMULA");
}

void MathViewModel::startCalculate()
{
	sp_DataModel->LoadforCalc();
	sp_Notification->trigger("RESULT");
}
