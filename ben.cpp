#include <iostream>
#include "ben_common.h"
#include "ben.h"
#include "ben_view.h"
#include "ben_server.h"


void Ben::start() {
	std::cout << "greetings, planet\n";
	BenView::Instance()->startCurses();
}

void Ben::stop() {
	std::cout << "farewell, planet\n";
	BenServer::Instance()->stop();
	BenView::Instance()->stopCurses();
}

void Ben::hideCursor() {
	BenView::Instance()->hideCursor();
}

BenWidget* Ben::createWidget(std::string lookup, BenWidgetType widgetType, int sizeX, int sizeY, int posX, int posY) {
	BenWidget* widget = new BenWidget();
	widget->lookup = lookup;
	widget->sizeX = sizeX;
	widget->sizeY = sizeY;
	widget->posX = posX;
	widget->posY = posY;

	widget->type = widgetType;

	BenView::Instance()->insertWidget(widget);

	return widget;
}

BenWidget* Ben::widget(std::string lookup) {
	return BenView::Instance()->getWidget(lookup);
}

int Ben::maxHeight() {
	return BenView::Instance()->getMaxHeight();
}

int Ben::maxWidth() {
	return BenView::Instance()->getMaxWidth();
}