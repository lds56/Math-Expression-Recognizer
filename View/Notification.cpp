#include "Notification.h"

void Notification::trigger(const char *p)
{
	sp_View->reflash(p);
}