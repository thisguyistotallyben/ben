#pragma once

#include <queue>
#include <thread>
#include "ben_common.h"


class BenServer {
public:
	static BenServer* Instance();
	void serve();
	void stop();
	void addEvent(BenEvent* event);
	bool hasWaitingEvent();
private:
	BenServer() {};
	BenServer(BenServer const&) {};
	BenServer& operator=(BenServer const&) {};
	static BenServer* bs_Singleton_Instance;

	std::thread* eventHandlerThread;
	std::queue<BenEvent*> events;

	void ThreadedEventHandler();
	BenEvent* getNextEvent();
	void performEvent(BenEvent* event);
};