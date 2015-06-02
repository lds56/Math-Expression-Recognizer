#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_
#include "View\mathmainwindow.h"
#include "Common\BaseNotification.h"
#include <memory>
using namespace std;

class MathMainWindow;
class Notification:public BaseNotification
{
public:
	Notification(){}
	virtual ~Notification(){}
	void set(shared_ptr<MathMainWindow> p){sp_View=p;}
	virtual void trigger(const char *p);
private:
	shared_ptr<MathMainWindow> sp_View;
};

#endif
