#include <iostream>
#include <queue>


enum BenWidgetType {
	BEN_BORDERED_BOX
};


class BenWidget {

};


class BenEvent {
public:
	std::string eventType;
};


class BenVisual {
public:
	static BenVisual* Instance();
	void startCurses();
	void stopCurses();
	void addEvent(std::string name, BenWidgetType, int sizex, int sizey, int posx, int posy);
	void check();
private:
	BenVisual() {};
	BenVisual(BenVisual const&) {};
	BenVisual& operator=(BenVisual const&) {};
	static BenVisual* bv_Singleton_Instance;
	
	std::queue<BenEvent> events;
};


class Ben {
public:
	void start();
	void stop();

	BenWidget createWidget(std::string lookup, BenWidgetType, int sizex, int sizey, int posx, int posy);
	BenWidget widget(std::string lookup);
};
