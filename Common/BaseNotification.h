#ifndef BASENOTIFICATION_H_
#define BASENOTIFICATION_H_

class BaseNotification
{
public:
	BaseNotification(){}
	virtual ~BaseNotification(){}
	virtual void trigger(const char* p)=0;
};

#endif
