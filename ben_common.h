#pragma once

#include <iostream>
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

	int sizeX;
	int sizeY;
	int posX;
	int posY;

	bool visible;

	WINDOW *win;
	PANEL *panel;

	void show();
	void hide();
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