#include <mutex>
#include <stddef.h>
#include <condition_variable>
#include "ben.h"
#include "ben_view.h"
#include "ben_server.h"

BenServer* BenServer::bs_Singleton_Instance = NULL;

std::mutex mtx;
std::condition_variable cv;
BenView* bv = BenView::Instance();


BenServer* BenServer::Instance() {
	if (bs_Singleton_Instance == NULL) {
		bs_Singleton_Instance = new BenServer();
	}
	return bs_Singleton_Instance;
}

bool hasEvents() {
	return BenServer::Instance()->hasWaitingEvent();
}

void BenServer::ThreadedEventHandler() {
	bool cont = true;

	while(cont) {
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, hasEvents);
		
		while (hasWaitingEvent()) {
			BenEvent* event = getNextEvent();
			if (event->eventType == DIE) {
				cont = false;
				break;
			}
			performEvent(event);
			delete event;
		}
	}
}

void BenServer::performEvent(BenEvent* event) {

	switch(event->eventType) {
		case SHOW_HIDE:
			if (event->visible) {
				bv->showWidget(event->widget);
			}
			else {
				bv->hideWidget(event->widget);
			}
			break;
		default: break;
	}
}

void BenServer::serve() {
	eventHandlerThread = new std::thread(&BenServer::ThreadedEventHandler, this);
}

void BenServer::stop() {
	BenEvent* dieEvent = new BenEvent();
	dieEvent->eventType = DIE;
	addEvent(dieEvent);
	eventHandlerThread->join();
}

void BenServer::addEvent(BenEvent* event) {
	events.push(event);
	cv.notify_one();
}

bool BenServer::hasWaitingEvent() {
	return !events.empty();
}

BenEvent* BenServer::getNextEvent() {
	BenEvent* event = events.front();
	events.pop();
	return event;
}