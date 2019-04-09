#include "interactivePusheenMenu.h"

#include "textureBaking.h"

#include "commonMath.h"
#include "commonDraw.h" //Screen clearing

#include <iostream>

#include <conio.h>

#include "simpleTimer.h"

#include <fstream>

const int CATOPTSCOUNT = 42;

interactivePusheenMenu::interactivePusheenMenu() {
	targetCat = nullptr;
	catTexture = nullptr;
	cursorPos = 0;
}

interactivePusheenMenu::interactivePusheenMenu(pusheenCat *_cat, mippedTexture *_tex) {
	targetCat = _cat;
	catTexture = _tex;
	cursorPos = 0;
}

interactivePusheenMenu::~interactivePusheenMenu() {

}

void interactivePusheenMenu::rebakeCat() {
	std::cout << "\nRebaking with your "<<std::thread::hardware_concurrency()<<" threads...";
	simpleTimer timer;
	targetCat->updateCat();
	threadedBake(*catTexture, samplePusheen, *targetCat, std::thread::hardware_concurrency());
	std::cout << " Bake took " << timer.press() << "ms.\n";
}

void interactivePusheenMenu::printMenu() {
	for (int i = 0; i < CATOPTSCOUNT; i++) {
		if (i == cursorPos) {
			std::cout << ">";
		} else {
			std::cout << " ";
		}
		std::cout << catOptions[i] << ":" << (*targetCat)[i] << std::endl;
		if(i==cursorPos) std::cout << "\t" << catDescriptions[i] << std::endl;
	}
}

#include "genericPtr.h"

void interactivePusheenMenu::importCatData() {
	std::ifstream inFile("pusheenCatData.ini");
	if (!inFile.good()) {
		std::cout << "\n! Failed to open pusheenCatData.ini! Is the file missing?\n";
		return;
	}
	double newval = 0;
	for (int i = 0; i < CATOPTSCOUNT; i++) {
		// TODO: Find out why this doesn't work if you put in the cat[i] directly, and fix it.
		genericPtr ph = (*targetCat)[i];
		inFile >> ph;
		// ??? Doesn't work if you put in targetCat[i] directly
		// But output does!
	}
	std::cout << "\nSuccessfully imported cat settings...\n Press any movement key to refresh the settings panel.\n";
}

#include <filesystem>//for current_path

void interactivePusheenMenu::exportCatData() {
	std::ofstream outFile("pusheenCatData.ini");
	if (!outFile.good()) {
		std::cout << "\n! Failed to open pusheenCatData.ini when trying to write!\n";
		return;
	}
	for (int i = 0; i < CATOPTSCOUNT; i++) {
		outFile << (*targetCat)[i] << " ";
	}
	std::cout << "\nSuccessfully exported cat settings in " << std::experimental::filesystem::current_path() <<" ...\n";
}

void menuThread(interactivePusheenMenu* menu) {
	int in=0;
	double incr = 0.1;
	while (menu->cursorPos!=-1) {
		clearScreen();
		
		std::cout << "To move up or down the menu, press W or S respectively.\nTo increment or decrement a specific value, press D or A respectively.\n";
		menu->printMenu();
		std::cout << "\nIncrement: " << incr << std::endl;
		std::cout	<< "To alter the increment, use j and l.\nTo import or export the cat settings, press i or p respectively.\n"
					<< "To rebake the cat, press X. To end the program, press Y.\n";

		//If we don't want to refresh the screen, we goto here.
		norefresh:

		in = _getch();
		///TODO: fatass switch?
		if (in == 'a' || in == 'A')
			(*menu->targetCat)[menu->cursorPos] -= incr;
		if (in == 'd' || in == 'D')
			(*menu->targetCat)[menu->cursorPos] += incr;
		if (in == 's' || in == 'S')
			menu->cursorPos = clampF(menu->cursorPos + 1, 0, CATOPTSCOUNT-1);
		if (in == 'w' || in == 'W')
			menu->cursorPos = clampF(menu->cursorPos - 1, 0, CATOPTSCOUNT-1);
		if (in == 'l' || in == 'L')
			incr += 0.0025;
		if (in == 'j' || in == 'J')
			incr -= 0.0025;
		if (in == 'i' || in == 'I'){
			menu->importCatData();
			goto norefresh;
		}
		if (in == 'p' || in == 'P'){
			menu->exportCatData();
			goto norefresh;
		}
		if (in == 'x' || in == 'X'){
			menu->rebakeCat();
			goto norefresh;
		}
		if (in == 'y' || in == 'Y')
			menu->cursorPos = -1;
	}
}