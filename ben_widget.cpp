#include "ben_common.h"
#include "ben_server.h"


void BenWidget::show() {
	BenEvent* event = new BenEvent();
	event->eventType = SHOW_HIDE;
	event->visible = true;
	event->widget = this;
	BenServer::Instance()->addEvent(event);
}