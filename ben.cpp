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
	event.lookup = lookup;
	event.sizex = sizex;
	event.sizey = sizey;
	event.posx = posx;
	event.posy = posy;
	BenVisual::Instance()->addEvent(event);
	return BenWidget(); // probably make this return the actual widget, not some dummy nothing
}

BenWidget Ben::widget(std::string lookup) {
	BenWidget* w = BenVisual::Instance()->getWidget(lookup);
	std::cout << "in widget: " << w->lookup << std::endl;
	return *w;
}

void BenWidget::show() {
	std::cout << "in show: " << this->lookup;
	BenEvent event;
	event.eventType = SHOW_HIDE;
	event.visible = true;
	event.widget = this;
	BenVisual::Instance()->addEvent(event);
}
