#pragma once

//Symbols:
//A B C D E F G H I J K L M N O P Q R S T U V W X Y Z  [0...25]
// [ ] . ! ? + - * / ' : [26...37]
// 0 1 2 3 4 5 6 7 8 9 [38...47]
//The magical 48 is an empty space... How sweet.

#include <string>
#include "vec2.h"

short translateChar(char symb);

bool sampleText(vec2 pos, std::string text);
