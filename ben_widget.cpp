#include "ben_common.h"
#include "ben_server.h"


void BenWidget::show() {
	this->visible = true;

	BenEvent* event = new BenEvent();
	event->eventType = SHOW_HIDE;
	event->widget = this;
	BenServer::Instance()->addEvent(event);
}

void BenWidget::hide() {
	this->visible = false;

	BenEvent* event = new BenEvent();
	event->eventType = SHOW_HIDE;
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