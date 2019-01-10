#pragma once

#include "pusheenCat.h"
#include <string>

const std::string catOptions[] = {
	"Unavailable",//"Is the cat retaded?",
	"Unavailable",//"Does the cat have an OwO face?",
	"Unavailable",//"Retarded cat's iris distance",
	"Generic distance for eyes and ears",
	"Eye size",//4...
	"Foot size",
	"Foot count",
	"How fat the cat's front is",
	"How fat the cat's back is",
	"How inset the butt's top is",//9..
	"The radius of the back circles",
	"Cat height",
	"Cat length",
	"Whiskers' number on each side",
	"Whiskers' length",
	"Tail length",//15...
	"Tail size",
	"Ears' size",
	"Unavailable",//"The tail type",
	"Unavailable",//"The eybrow type",
	"Unavailable",//"The mouth type",
	"Border thickness",
	"Border color R",
	"Border color G",
	"Border color B",//24
	"Eye color R",
	"Eye color G",
	"Eye color B",
	"Tail stripe color R",
	"Tail stripe color G",
	"Tail stripe color B",//30
	"Fur color R",
	"Fur color G",
	"Fur color B",
	"Bottom left whisker angle",
	"Left side whiskers fake occlusion factor",//35
};

struct interactivePusheenMenu {

	pusheenCat* targetCat;
	mippedTexture* catTexture;
	int cursorPos;

	void setCatData(int index, double val);
	void modifyCatData(int index,double val);
	double getCatData(int index);
	void rebakeCat();
	void printMenu();

	void exportCatData();
	void importCatData();

	interactivePusheenMenu();
	interactivePusheenMenu(pusheenCat *_cat, mippedTexture *_tex);
	~interactivePusheenMenu();
};

void menuThread(interactivePusheenMenu* menu);