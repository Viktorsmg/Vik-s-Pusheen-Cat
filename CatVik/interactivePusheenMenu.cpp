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

void interactivePusheenMenu::setCatData(int index, double val) {
	switch (index) {
		case 0:
			targetCat->retarded = val > 0.5; break;
		case 1:
			break;//OwO here
		case 2:
			targetCat->eyeDistMod = val; break;
		case 3:
			targetCat->genericDist = val; break;
		case 4:
			targetCat->eyeSize = val; break;
		case 5:
			targetCat->footSize = val; break;
		case 6:
			//To ensure no rounding errors, we'll slightly increase the result.
			targetCat->footCount = val; break;
		case 7:
			targetCat->frontFat = val; break;
		case 8:
			targetCat->backFat = val; break;
		case 9:
			targetCat->backInset = val; break;
		case 10:
			targetCat->backCircleR = val; break;
		case 11:
			targetCat->height = val; break;
		case 12:
			targetCat->length = val; break;
		case 13:
			targetCat->whiskerCount = val; break;
		case 14:
			targetCat->whiskerLen = val; break;
		case 15:
			targetCat->tailLen = val; break;
		case 16:
			targetCat->tailSize = val; break;
		case 17:
			targetCat->earSize = val; break;
		case 18:
			break; //tail type
		case 19:
			break; //eyebrow type
		case 20:
			break; //mouth type
		case 21:
			targetCat->borderThickness = val; break;
		case 22:
			targetCat->borderColor.x = val; break;
		case 23:
			targetCat->borderColor.y = val; break;
		case 24:
			targetCat->borderColor.z = val; break;
		case 25:
			targetCat->eyeColor.x = val; break;
		case 26:
			targetCat->eyeColor.y = val; break;
		case 27:
			targetCat->eyeColor.z = val; break;
		case 28:
			targetCat->tailColor.x = val; break;
		case 29:
			targetCat->tailColor.y = val; break;
		case 30:
			targetCat->tailColor.z = val; break;
		case 31:
			targetCat->furColor.x = val; break;
		case 32:
			targetCat->furColor.y = val; break;
		case 33:
			targetCat->furColor.z = val; break;
		case 34:
			targetCat->whiskerAng = val; break;
		case 35:
			targetCat->whiskerFakeOccl = val; break;
		case 36:
			targetCat->uvoffset.x = val; break;
		case 37:
			targetCat->uvoffset.y = val; break;
		case 38:
			targetCat->uvscale.x = val; break;
		case 39:
			targetCat->uvscale.y = val; break;
		case 40:
			targetCat->tailBotFac = val; break;
		case 41:
			targetCat->tailTopFac = val; break;

		default: break;
	}
}

void interactivePusheenMenu::modifyCatData(int index, double val) {
	switch (index) {
		case 0:
			targetCat->retarded = val > 0.0; break;
		case 1:
			break;//OwO here
		case 2:
			targetCat->eyeDistMod += val; break;
		case 3:
			targetCat->genericDist += val; break;
		case 4:
			targetCat->eyeSize += val; break;
		case 5:
			targetCat->footSize += val; break;
		case 6:
			//To ensure no rounding errors, we'll slightly increase the result.
			targetCat->footCount += sign(val); break;
		case 7:
			targetCat->frontFat += val; break;
		case 8:
			targetCat->backFat += val; break;
		case 9:
			targetCat->backInset += val; break;
		case 10:
			targetCat->backCircleR += val; break;
		case 11:
			targetCat->height += val; break;
		case 12:
			targetCat->length += val; break;
		case 13:
			targetCat->whiskerCount += sign(val); break;
		case 14:
			targetCat->whiskerLen += val; break;
		case 15:
			targetCat->tailLen += val; break;
		case 16:
			targetCat->tailSize += val; break;
		case 17:
			targetCat->earSize += val; break;
		case 18:
			break; //tail type
		case 19:
			break; //eyebrow type
		case 20:
			break; //mouth type
		case 21:
			targetCat->borderThickness += val; break;
		case 22:
			targetCat->borderColor.x += val; break;
		case 23:
			targetCat->borderColor.y += val; break;
		case 24:
			targetCat->borderColor.z += val; break;
		case 25:
			targetCat->eyeColor.x += val; break;
		case 26:
			targetCat->eyeColor.y += val; break;
		case 27:
			targetCat->eyeColor.z += val; break;
		case 28:
			targetCat->tailColor.x += val; break;
		case 29:
			targetCat->tailColor.y += val; break;
		case 30:
			targetCat->tailColor.z += val; break;
		case 31:
			targetCat->furColor.x += val; break;
		case 32:
			targetCat->furColor.y += val; break;
		case 33:
			targetCat->furColor.z += val; break;
		case 34:
			targetCat->whiskerAng += val; break;
		case 35:
			targetCat->whiskerFakeOccl += val; break;
		case 36:
			targetCat->uvoffset.x += val; break;
		case 37:
			targetCat->uvoffset.y += val; break;
		case 38:
			targetCat->uvscale.x += val; break;
		case 39:
			targetCat->uvscale.y += val; break;
		case 40:
			targetCat->tailBotFac += val; break;
		case 41:
			targetCat->tailTopFac += val; break;

		default: break;
	}
}

double interactivePusheenMenu::getCatData(int index) {
	switch (index) {
		case 0:
			return targetCat->retarded; break;
		case 1:
			return 0; break;//OwO here
		case 2:
			 return targetCat->eyeDistMod; break;
		case 3:
			return targetCat->genericDist; break;
		case 4:
			return targetCat->eyeSize; break;
		case 5:
			return targetCat->footSize; break;
		case 6:
			//To ensure no rounding errors, we'll slightly increase the result.
			return targetCat->footCount; break;
		case 7:
			return targetCat->frontFat; break;
		case 8:
			return targetCat->backFat; break;
		case 9:
			return targetCat->backInset; break;
		case 10:
			return targetCat->backCircleR; break;
		case 11:
			return targetCat->height; break;
		case 12:
			return targetCat->length; break;
		case 13:
			return targetCat->whiskerCount; break;
		case 14:
			return targetCat->whiskerLen; break;
		case 15:
			return targetCat->tailLen; break;
		case 16:
			return targetCat->tailSize; break;
		case 17:
			return targetCat->earSize; break;
		case 18:
			return 0; break; //tail type
		case 19:
			return 0; break; //eyebrow type
		case 20:
			return 0; break; //mouth type
		case 21:
			return targetCat->borderThickness; break;
		case 22:
			return targetCat->borderColor.x; break;
		case 23:
			return targetCat->borderColor.y; break;
		case 24:
			return targetCat->borderColor.z; break;
		case 25:
			return targetCat->eyeColor.x; break;
		case 26:
			return targetCat->eyeColor.y; break;
		case 27:
			return targetCat->eyeColor.z; break;
		case 28:
			return targetCat->tailColor.x; break;
		case 29:
			return targetCat->tailColor.y; break;
		case 30:
			return targetCat->tailColor.z; break;
		case 31:
			return targetCat->furColor.x; break;
		case 32:
			return targetCat->furColor.y; break;
		case 33:
			return targetCat->furColor.z; break;
		case 34:
			return targetCat->whiskerAng; break;
		case 35:
			return targetCat->whiskerFakeOccl; break;
		case 36:
			return targetCat->uvoffset.x; break;
		case 37:
			return targetCat->uvoffset.y; break;
		case 38:
			return targetCat->uvscale.x; break;
		case 39:
			return targetCat->uvscale.y; break;
		case 40:
			return targetCat->tailBotFac; break;
		case 41:
			return targetCat->tailTopFac; break;

		default: 
			return -1; break;
	}

	//Number that couldn't have been set ordinarily; error-code. 1337 should remind you that something is off.
	return 0.1337;
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
		std::cout << catOptions[i] << ":" << getCatData(i) << std::endl;
		if(i==cursorPos) std::cout << "\t" << catDescriptions[i] << std::endl;
	}
}

void interactivePusheenMenu::importCatData() {
	std::ifstream inFile("pusheenCatData.ini");
	if (!inFile.good()) {
		std::cout << "\n! Failed to open pusheenCatData.ini! Is the file missing?\n";
		return;
	}
	double newval = 0;
	for (int i = 0; i < CATOPTSCOUNT; i++) {
		inFile >> newval;
		setCatData(i, newval);
	}
	std::cout << "\nSuccessfully imported cat settings...\n Press any movement key to refresh the settings panel.\n";
}

void interactivePusheenMenu::exportCatData() {
	std::ofstream outFile("pusheenCatData.ini");
	if (!outFile.good()) {
		std::cout << "\n! Failed to open pusheenCatData.ini when trying to write!\n";
		return;
	}
	for (int i = 0; i < CATOPTSCOUNT; i++) {
		outFile << getCatData(i) << " ";
	}
	std::cout << "\nSuccessfully exported cat settings...\n";
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
			menu->modifyCatData(menu->cursorPos, -incr);
		if (in == 'd' || in == 'D')
			menu->modifyCatData(menu->cursorPos, incr);
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