#pragma once
#include <SDL.h>

#include "ivec2.h"
#include "vec2.h"
#include "vec3.h"
#include "commonMath.h"
#include "mippedTexture.h"

void drawPixel(SDL_Renderer *renderer, ivec2 pos, ivec3 col);

void drawPixel(SDL_Renderer *renderer, ivec2 pos, vec3 col);

void drawPixel(SDL_Renderer *renderer, vec2 uv, vec3 col);

//Note: Frametime should be in miliseconds!
void drawFPS(SDL_Renderer *renderer, float frametime);

void drawTex(SDL_Renderer *renderer, const mippedTexture &tex, const ivec2 start, const ivec2 end);

//Clears the console screen
void clearScreen();

/*
Sad stuff :(
Only main thread can do SDL_Renderer stuff
I got the render section's coordinate scheduling right the first time! Oh well...

void threadedDrawSection(SDL_Renderer *renderer, const mippedTexture &tex, const ivec2 start, const ivec2 end);

void threadedDrawTex(SDL_Renderer *renderer, const mippedTexture &tex, ivec2 start, ivec2 end);
*/
