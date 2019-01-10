#pragma once

#include "pusheenCat.h"
#include <string>

const std::string catOptions[] = {
	"Unavailable",
	"Unavailable",
	"Unavailable",
	"Generic distance for eyes and ears",
	"Eye size",//4...
	"Foot size",
	"Foot count",
	"Cat front fat",
	"Cat back fat",
	"Butt top inset",//9..
	"Back circle radius",
	"Cat height",
	"Cat length",
	"Whiskers",
	"Whisker length",
	"Tail length",//15...
	"Tail size",
	"Ears' size",
	"Unavailable",
	"Unavailable",
	"Unavailable",
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
	"Whisker angle",
	"Whiskers fake occlusion factor",//35
	"UV offset X",
	"UV offset Y",
	"UV scale X",
	"UV scale Y"//39
};

const std::string catDescriptions[] = {
	"Meant to be whether the cat is retarded or not. Currently unavailable.",
	"Meant to be the type of eyes the cat has. Currently unavailable.",
	"Meant to be an additional eye modifier. Currently unavailable.",//Retarded cat's iris distance for example
	"Generic distance for the cat's eyes and ears...",
	"The radius of each eye.",//4...
	"The radius of each foot.",
	"The number of feet.",
	"How fat the cat's front is.",
	"How fat the cat's back is.",
	"How inset the butt's top is.",//9..
	"The radius of the back circles.",
	"How tall the cat is.",
	"How long the cat is.",
	"The number of whiskers on each side.",
	"The length of each individual whisker.",
	"The length of the tail.",//15...
	"The width of the tail.",
	"The height and width of the ears.",
	"Meant to be the type of tail coloration. Currently unavailable.",
	"Meant to be the type of eyebrows. Currently unavailable.",
	"Meant to be the type of mouth the cat has. Currently unavailable.",
	"How thick the borders of the cat are. Make the cat look more or less fuzzy/blurry.",
	"Red channel of the borders' color.",
	"Green channel of the borders' color.",
	"Blue channel of the borders' color.",//24
	"Red channel of the eye color.",
	"Green channel of the eye color.",
	"Blue channel of the eye color.",
	"Red channel of the tail stripes' color.",
	"Green channel of the tail stripes' color.",
	"Blue channel of the tail stripes' color.",//30
	"Red channel of the cat's fur/fill color.",
	"Green channel of the cat's fur/fill color.",
	"Blue channel of the cat's fur/fill color.",
	"Angle of the bottom whisker. The whiskers are distributed at equal angles between the bottom whisker and the top (X mirrored) whisker.",
	"Factor from 0 to 1 for how much the whiskers are cut off on the left side to simulate occlusion, or the cat having a 3d face or whatever.",//35
	"X offset for where the cat is located on the drawn texture. Use this to move the cat horizontally.",
	"Y offset for where the cat is located on the drawn texture. Use this to move the cat vertically.",
	"X scale for the cat. Use this to stretch/shrink the cat horizontally.",
	"Y scale for the cat. Use this to stretch/shrink the cat vertically."//39
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