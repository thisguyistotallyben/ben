#pragma once

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
	SHOW_HIDE,
	DIE
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


struct BenEvent {
	BenEventType eventType;

	BenWidget* widget;
	std::string lookup;
	BenBorderType borderType;
	int sizex;
	int sizey;
	int posx;
	int posy;

	bool visible;
};


class Ben {
public:
	void start();
	void stop();

	BenWidget createWidget(std::string lookup, BenWidgetType, int sizex, int sizey, int posx, int posy);
	BenWidget widget(std::string lookup);
	void hideCursor();
};
