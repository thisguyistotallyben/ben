#include "ben_common.h"
#include "ben_server.h"


void BenWidget::show() {
	BenEvent* event = new BenEvent();
	event->eventType = SHOW_HIDE;
	event->visible = true;
	event->widget = this;
	BenServer::Instance()->addEvent(event);
}

void BenWidget::hide() {
	BenEvent* event = new BenEvent();
	event->eventType = SHOW_HIDE;
	event->visible = false; // TODO: this is silly and should belong only on the widget
	event->widget = this;
	BenServer::Instance()->addEvent(event);
}

void BenWidget::move(int posX, int posY) {
	this->posX = posX;
	this->posY = posY;

	BenEvent* event = new BenEvent();
	event->eventType = MODIFY;
	event->widget = this;
	BenServer::Instance()->addEvent(event);
}