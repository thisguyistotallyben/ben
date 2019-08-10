#include <iostream>
#include <stddef.h>
#include <curses.h>
#include <panel.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ben_common.h"
#include "ben_view.h"


BenView* BenView::bv_Singleton_Instance = NULL;


BenView* BenView::Instance() {
	if (!bv_Singleton_Instance) {
		bv_Singleton_Instance = new BenView();
	}
	return bv_Singleton_Instance;
}

void BenView::startCurses() {
	std::cout << "ncurses starting\n";
	initscr();
	raw();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	noecho();
	refresh();

	enabled = true;
}

void BenView::stopCurses() {
	std::cout << "ncurses stopping\n";

	endwin();
}

bool BenView::isActive() {
	return enabled;
}

void BenView::insertWidget(BenWidget* widget) {
	widget->win = newwin(
		widget->sizeY,
		widget->sizeX,
		widget->posY,
		widget->posX
	);
	widget->panel = new_panel(widget->win);
	hide_panel(widget->panel);

	switch (widget->type) {
		case BEN_BOX:
			box(widget->win, 0, 0);
			break;
		default: break;
	}

	widgets[widget->lookup] = widget;
}

void BenView::updateView() {
	update_panels();
	doupdate();
}

void BenView::hideCursor() {
	curs_set(0);
}

BenWidget* BenView::getWidget(std::string lookup) {
	return widgets[lookup];
}

void BenView::showWidget(BenWidget* widget) {
	show_panel(widget->panel);
	updateView();
}

void BenView::hideWidget(BenWidget* widget) {
	hide_panel(widget->panel);
	updateView();
}

void BenView::moveWidget(BenWidget* widget) {
	wmove(widget->win, widget->posX, widget->posY);
	wrefresh(widget->win);
	updateView();
}

int BenView::getMaxHeight() {
	return LINES;
}

int BenView::getMaxWidth() {
	return COLS;
}