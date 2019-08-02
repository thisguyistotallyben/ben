#include <iostream>
#include "ben_common.h"
#include "ben.h"
#include "ben_view.h"
#include "ben_server.h"

void Ben::start() {
	std::cout << "greetings, planet\n";
	BenView::Instance()->startCurses();
	BenServer::Instance()->serve();
}

void Ben::stop() {
	std::cout << "farewell, planet\n";
	BenServer::Instance()->stop();
	BenView::Instance()->stopCurses();
}

void Ben::hideCursor() {
	BenView::Instance()->hideCursor();
}

BenWidget Ben::createWidget(std::string lookup, BenWidgetType widgetType, int sizeX, int sizeY, int posX, int posY) {
	BenWidget* widget = new BenWidget();
	widget->lookup = lookup;
	widget->sizeX = sizeX;
	widget->sizeY = sizeY;
	widget->posX = posX;
	widget->posY = posY;

	widget->type = widgetType;

	BenView::Instance()->insertWidget(widget);

	return *widget;
}

BenWidget Ben::widget(std::string lookup) {
	BenWidget* w = BenView::Instance()->getWidget(lookup);
	return *w;
}