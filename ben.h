#pragma once

#include <queue>
#include <map>
#include "ben_common.h"
#include "ben_server.h"


class Ben {
public:
	void start();
	void stop();

	BenWidget* createWidget(std::string lookup, BenWidgetType, int sizex, int sizey, int posx, int posy);
	BenWidget* widget(std::string lookup);
	void hideCursor();

	int maxHeight();
	int maxWidth();
};