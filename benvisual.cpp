#include <iostream>
#include <stddef.h>
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
}

void BenVisual::stopCurses() {
	std::cout << "ncurses stopping\n";
}

void BenVisual::check() {
	std::cout << "suh, doo\n";
}
