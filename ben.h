#include <iostream>
#include <queue>
#include <map>
#include <thread>
#include <curses.h>
#include <panel.h>


enum BenWidgetType {
	BEN_BOX
};

enum BenBorderType {
	BEN_FULL,
	BEN_TEXT,
	BEN_NO_BORDER
};

enum BenEventType {
	CREATE,
	DESTROY,
	MODIFY,
	SHOW_HIDE,
	DIE
};


struct BenEvent {
	BenEventType eventType;

	std::string lookup;
	BenBorderType borderType;
	int sizex;
	int sizey;
	int posx;
	int posy;

	bool visible;
};


class BenWidget {
public:
	std::string lookup;
	BenWidgetType type;

	int sizex;
	int sizey;
	int posx;
	int posy;

	bool visible;

	WINDOW *win;
	PANEL *panel;

	void show();
};


class BenVisual {
public:
	static BenVisual* Instance();

	void startCurses();
	void stopCurses();

	void addEvent(BenEvent event);
	bool hasWaitingEvent();
	BenEvent getNextEvent();

	void insertWidget(BenWidget* widget);

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
