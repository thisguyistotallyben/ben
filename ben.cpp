#include <iostream>
#include "ben.h"


void Ben::start() {
	std::cout << "greetings, planet\n";
}

void Ben::stop() {
	std::cout << "farewell, planet\n";
}


BenWidget Ben::createWidget(std::string lookup, BenWidgetType, int sizex, int sizey, int posx, int posy) {
	return BenWidget();
}

BenWidget Ben::widget(std::string lookup) {
	return BenWidget();
}
