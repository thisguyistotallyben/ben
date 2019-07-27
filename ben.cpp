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
	return BenWidget();
}

BenWidget Ben::widget(std::string lookup) {
	return BenWidget();
}
