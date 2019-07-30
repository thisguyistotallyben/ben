#include <iostream>
#include <stddef.h>
#include <curses.h>
#include <panel.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "benview.h"


BenView* BenView::bv_Singleton_Instance = NULL;

std::mutex mtx;
std::condition_variable cv;


bool hasEvents() {
	return BenView::Instance()->hasWaitingEvent();
}

void bvQueueHandler() {
	BenView* bv = BenView::Instance();
	bool guessilldie = false;
	BenWidget *widget;

	while(1) {
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, hasEvents);
		
		while (bv->hasWaitingEvent()) {
			BenEvent event = bv->getNextEvent();
			switch(event.eventType) {
				case SHOW_HIDE:
					widget = event.widget;

                    if (event.visible) {
					    if (widget->panel != NULL) {
						    show_panel(widget->panel);
					    }
                    }
                    else {
                        if (widget->panel != NULL) {
						    hide_panel(widget->panel);
					    }
                    }

					bv->updateView();
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
	queueHandlerThread = new std::thread(bvQueueHandler);
}

void BenView::stopCurses() {
	std::cout << "ncurses stopping\n";
	stopQueueHandler();

	endwin();
}

bool BenView::hasWaitingEvent() {
	return !events.empty();
}

BenEvent BenView::getNextEvent() {
	BenEvent event = events.front();
	events.pop();
	return event;
}

void BenView::addEvent(BenEvent event) {
    //std::unique_lock<std::mutex> lck(mtx);
	events.push(event);
	cv.notify_one();
}

bool BenView::isActive() {
	return enabled;
}

void BenView::stopQueueHandler() {
	BenEvent dieEvent;
	dieEvent.eventType = DIE;
	addEvent(dieEvent);
	queueHandlerThread->join();
}

void BenView::insertWidget(BenWidget* widget) {
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
