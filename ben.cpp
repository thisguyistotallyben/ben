#include <iostream>
#include "ben.h"


void Ben::start() {
	std::cout << "greetings, planet\n";
	BenVisual::Instance()->startCurses();
}

void Ben::stop() {
	std::cout << "farewell, planet\n";
	BenVisual::Instance()->stopCurses();
}


BenWidget Ben::createWidget(std::string lookup, BenWidgetType, int sizex, int sizey, int posx, int posy) {
	std::cout << "creating a widget\n";
	BenEvent event;
	event.eventType = CREATE;
	BenVisual::Instance()->addEvent(event);
	return BenWidget(); // probably make this return the actual widget, not some dummy nothing
}

BenWidget Ben::widget(std::string lookup) {
	return BenWidget();
}

void BenWidget::show() {
	BenEvent event;
	event.eventType = SHOW_HIDE;
	event.visible = true;
	sendEvent(event);
}


// litle helper boi
void sendEvent(Event e) {
	BenVisual::Instance()->addEvent(e);
}
