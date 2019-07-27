#include <iostream>
#include <stddef.h>
#include <curses.h>
#include "ben.h"


// Singleton visuals so everything can access its functions
BenVisual* BenVisual::bv_Singleton_Instance = NULL;


BenVisual* BenVisual::Instance() {
	if (!bv_Singleton_Instance) {
		bv_Singleton_Instance = new BenVisual();
	}
	return bv_Singleton_Instance;
}

void BenVisual::startCurses() {
	std::cout << "ncurses starting\n";
	initscr();
	raw();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	noecho();
	refresh();
}

void BenVisual::stopCurses() {
	std::cout << "ncurses stopping\n";
	endwin();
}

void BenVisual::check() {
	std::cout << "suh, doo\n";
}
