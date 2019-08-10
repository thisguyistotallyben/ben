#include <iostream>
#include "ben.h" // BETTER, EASIER NCURSES

/*

Create widgets
ben.createWidget('box1', ben::BORDERED_BOX, 10, 10, 0, 0);

So you have a box and you want to display it...
ben.widget('box1')->display();
ben.display('box1');

Hide it?
ben.widget('box1').hide();

Move it?
ben.widget('box1').move(5, 5);

Less specifically?
ben.widget('box1').move(ben.widget('box2').getPositionRight());


You want to turn groups of widgets on and off as 'screens'?

ben.createWidgetGroup('group1');

Add widgets to group.
ben.group('group1').addWidget('box1');
OR
ben.group('group1').addWidgets('box1', 'box2', ...);

Display group.
ben.group('group1').display();

Hide it.
ben.group('group1').hide();


Widget types:
BORDERED_BOX
NO_BORDER_BOX
TEXT_INPUT
TEXT_DISPLAY

Attributes:
ben.widget('widgetId').setColorProfile(COLOR_PROFILE);


Advanced bullcrappery:
ben.dialog('This is text for the dialog', ben::WARNING_BANNER, 3);
OR
ben.dialog('This is an error', ben::ERROR_BANNER, 5);

Color types:
WARNING (black on yellow)
ERROR (white on red)
GOOD (white on green)
STANDARD (black on white)

Posiiton types:
TOP
BOTTOM
CENTER


*/

int main() {
	Ben ben;

	ben.start();
	ben.hideCursor();

	ben.createWidget(
		"header",
		BEN_BOX,
		ben.maxWidth(), 3,
		0, 0
	)->show();

	ben.createWidget(
		"footer",
		BEN_BOX,
		ben.maxWidth(), 3,
		0, ben.maxHeight() - 3
	)->show();

	ben.createWidget(
		"box1",
		BEN_BOX,
		30, 3,
		0, 3
	)->show();

	ben.createWidget(
		"box2",
		BEN_BOX,
		30, 10,
		0, 6
	)->show();

	ben.createWidget(
		"box3",
		BEN_BOX,
		5, 5,
		27, 3
	)->show();

	std::cin.ignore();

	BenWidget* w = ben.widget("box3");
	for (int i = 0; i < 5; i++) {
		w->move(w->posX + 1, w->posY); // does not work yet
		std::cin.ignore();
	}

	ben.widget("box3")->hide();

	std::cin.ignore();

	ben.stop();

	return 0;
}
