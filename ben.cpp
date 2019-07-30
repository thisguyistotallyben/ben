#include <iostream>
#include "ben.h"
#include "benview.h"

void Ben::start() {
	std::cout << "greetings, planet\n";
	BenView::Instance()->startCurses();
}

void Ben::stop() {
	std::cout << "farewell, planet\n";
	BenView::Instance()->stopCurses();
}

void Ben::hideCursor() {
    BenView::Instance()->hideCursor();
}

BenWidget Ben::createWidget(std::string lookup, BenWidgetType widgetType, int sizex, int sizey, int posx, int posy) {
	BenWidget* widget = new BenWidget();
	widget->lookup = lookup;
	widget->posx = posx;
	widget->posy = posy;
	// finish filling in actual info

	widget->win = newwin(
		sizey,
		sizex,
		posy,
		posx
	);
	wrefresh(widget->win);

	widget->panel = new_panel(widget->win);
	hide_panel(widget->panel);

	BenView::Instance()->insertWidget(widget);

	switch (widgetType) {
		case BEN_BOX:
			box(widget->win, 0, 0);
			break;
		default: break;
	}

    return *widget;
}

BenWidget Ben::widget(std::string lookup) {
	BenWidget* w = BenView::Instance()->getWidget(lookup);
	return *w;
}

void BenWidget::show() {
	BenEvent event;
	event.eventType = SHOW_HIDE;
	event.visible = true;
	event.widget = this;
	BenView::Instance()->addEvent(event);
}
