#ifndef BASECOMMAND_H_
#define BASECOMMAND_H_
#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
class BaseCommand //abstract class
{
public:
	BaseCommand(){}
	virtual ~BaseCommand(){};
	virtual void execute() = 0;
	virtual void execute(IplImage*) = 0;
};

#endif
