#pragma once

#include "ben.h"

class BenView {
public:
	static BenView* Instance();

	void startCurses();
	void stopCurses();

	void addEvent(BenEvent event);
	bool hasWaitingEvent();
	BenEvent getNextEvent();

	void insertWidget(BenWidget* widget);
	BenWidget* getWidget(std::string lookup);

	bool isActive();
	void updateView();
	void hideCursor();
private:
	BenView() {};
	BenView(BenView const&) {};
	BenView& operator=(BenView const&) {};
	static BenView* bv_Singleton_Instance;
	
	std::map<std::string, BenWidget*> widgets;
	std::queue<BenEvent> events;

	std::thread* queueHandlerThread;
	void stopQueueHandler();
	bool enabled;
};
