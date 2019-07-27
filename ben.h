#include <iostream>
#include <queue>
#include <map>
#include <thread>


enum BenWidgetType {
	BEN_BORDERED_BOX
};


class BenWidget {
public:
	std::string lookup;
	BenWidgetType type;

	int sizex;
	int sizey;
	int posx;
	int posy;
};


enum BenEventType {
	CREATE,
	DESTROY,
	MOVE,
	DIE
};


class BenEvent {
public:
	BenEventType eventType;
};


class BenVisual {
public:
	static BenVisual* Instance();

	void startCurses();
	void stopCurses();

	void addEvent(BenEvent event);
	bool hasWaitingEvent();
	BenEvent getNextEvent();

	bool isActive();
private:
	BenVisual() {};
	BenVisual(BenVisual const&) {};
	BenVisual& operator=(BenVisual const&) {};
	static BenVisual* bv_Singleton_Instance;
	
	std::map<std::string, BenWidget*> widgets;
	std::queue<BenEvent> events;

	std::thread* queueHandlerThread;
	void stopQueueHandler();
	bool enabled;
};


class Ben {
public:
	void start();
	void stop();

	BenWidget createWidget(std::string lookup, BenWidgetType, int sizex, int sizey, int posx, int posy);
	BenWidget widget(std::string lookup);
};
