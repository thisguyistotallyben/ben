#include <iostream>
#include <stddef.h>
#include <curses.h>
#include <panel.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ben.h"


BenVisual* BenVisual::bv_Singleton_Instance = NULL;

std::mutex mtx;
std::condition_variable cv;


bool hasEvents() {
	return BenVisual::Instance()->hasWaitingEvent();
}

void bvQueueHandler() {
	BenVisual* bv = BenVisual::Instance();
	bool guessilldie = false;
	BenWidget *widget;

	while(1) {
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, hasEvents);
		
		while (bv->hasWaitingEvent()) {
			BenEvent event = bv->getNextEvent();
			switch(event.eventType) {
				case CREATE:
					widget = new BenWidget();
					widget->lookup = event.lookup;
					widget->posx = event.posx;
					widget->posy = event.posy;
					// finish filling in actual info

					widget->win = newwin(
						event.sizey,
						event.sizex,
						event.posy,
						event.posx
					);
					wrefresh(widget->win);

					widget->panel = new_panel(widget->win);
					hide_panel(widget->panel);

					bv->insertWidget(widget);

					switch(event.borderType) {
						case BEN_BOX:
							box(widget->win, 0, 0);
							break;
						default: break;
					}
					// create new widget here
					break;
				case DESTROY:
					// destroy widget here
					break;
				case MODIFY:
					// change properties here
					break;
				case SHOW_HIDE:
					widget = bv->getElement(event.lookup);
					PANEL *p = widget->panel;
					if (p != NULL) show_panel(p);
					// show or hide the widget here
					break;
				case DIE:
					guessilldie = true;
					break;
				default:
					std::cout << "lol a thing\n";
					break;
			}
		}
		if (guessilldie) break;
	}
}



/*
	while(1) {
		std::cout << "in loop\n";
		std::unique_lock<std::mutex> lck(mtx);
		while(!bv->hasWaitingEvent()) {
			std::cout << "in waiting loop\n";
			if (!bv->isActive()) break;
			cv.wait(lck);
		}
		if (!bv->isActive()) break;
		std::cout << "past lock";
		while(bv->hasWaitingEvent()) {
			std::cout << bv->getNextEvent().eventType;
		}
	}
}
*/



BenVisual* BenVisual::Instance() {
	if (!bv_Singleton_Instance) {
		bv_Singleton_Instance = new BenVisual();
	}
	return bv_Singleton_Instance;
}

void BenVisual::startCurses() {
/*
	std::cout << "ncurses starting\n";
	initscr();
	raw();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	noecho();
	refresh();
*/

	enabled = true;
	queueHandlerThread = new std::thread(bvQueueHandler);
}

void BenVisual::stopCurses() {
	std::cout << "ncurses stopping\n";
	stopQueueHandler();

	endwin();
}

bool BenVisual::hasWaitingEvent() {
	return !events.empty();
}

BenEvent BenVisual::getNextEvent() {
	BenEvent event = events.front();
	events.pop();
	return event;
}

void BenVisual::addEvent(BenEvent event) {
	events.push(event);
	cv.notify_one();
}

bool BenVisual::isActive() {
	return enabled;
}

void BenVisual::stopQueueHandler() {
	BenEvent dieEvent;
	dieEvent.eventType = DIE;
	addEvent(dieEvent);
	queueHandlerThread->join();
}

void BenVisual::insertWidget(BenWidget* widget) {
	widgets.insert(make_pair(widget->lookup, widget));
}
