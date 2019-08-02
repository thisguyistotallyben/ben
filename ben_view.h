#pragma once

#include <map>
#include "ben_common.h"

class BenView {
public:
	static BenView* Instance();

	void startCurses();
	void stopCurses();

	void insertWidget(BenWidget* widget);
	void showWidget(BenWidget* widget);
	void hideWidget(BenWidget* widget);
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
	bool enabled;

};