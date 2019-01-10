#include "commonDraw.h"
#include "defines.h"
#include <SDL.h>

#include "ivec2.h"
#include "vec2.h"
#include "vec3.h"
#include "commonMath.h"
#include "textDrawing.h"

#include <thread>

#ifdef _WIN32
//Screen clearing with windows.h.
//If you're not on windows, fix the wrapper function below, which uses system("cls"),
//it still clears the screen.
//No other uses of windows.h should be present...
#include <Windows.h>
#else
#error You need to implement a terminal-clearing function before you can proceed.
//Look for this, and fix it:
/*

void clearScreen() {
system("cls");
}

*/
#endif



void drawPixel(SDL_Renderer *renderer, ivec2 pos, ivec3 col) {
	SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 0);
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

void drawPixel(SDL_Renderer *renderer, ivec2 pos, vec3 col) {
	ivec3 icol = fcivec(col);
	SDL_SetRenderDrawColor(renderer, icol.x, icol.y, icol.z, 0);
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

void drawPixel(SDL_Renderer *renderer, vec2 uv, vec3 col) {
	ivec3 icol = fcivec(col);
	//cout << icol.x << " " << icol.y << " " << icol.z << "       ";
	SDL_SetRenderDrawColor(renderer, icol.x, icol.y, icol.z, 0);
	SDL_RenderDrawPoint(renderer, int(uv.x*WX + 0.5), int(uv.y*WY + 0.5));
}

//Note: Frametime should be in miliseconds!
void drawFPS(SDL_Renderer *renderer, float frametime) {
	for (int i = 0; i < 24 * 13; i++) {
		for (int j = 0; j < 24; j++) {
			drawPixel(renderer, ivec2(i, j), vec3(0.0, 1.0*sampleText(vec2(i / 24.0, j / 24.0), std::string("FPS: ") + std::to_string(1000.0 / frametime)), 0.0));
			//drawPixel(renderer, ivec2(i, j), vec3(5.0, j / 48.0, 0.0));
		}
	}

}

void drawTex(SDL_Renderer *renderer, const mippedTexture &tex, const ivec2 start, const ivec2 end) {
	ivec2 diff = end - start;
	for (int i = start.x; i < end.x; i++) {
		for (int j = start.y; j < end.y; j++) {
			drawPixel(renderer, ivec2(i, j), 
					  tex.sample(vec2(double(i-start.x) / diff.x, double(j-start.y) / diff.y)));
		}
	}
}

void clearScreen() {
	system("cls");
}

/*
void threadedDrawSection(SDL_Renderer *renderer, const mippedTexture &tex, const ivec2 start, const ivec2 end) {
	//std::printf("Drawing thread section. Coordinates: (%d,%d), (%d,%d)\n", start.x, start.y, end.x, end.y);
	//std::printf("Texture color at (0,0): (%fr,%fg,%fb)\n", tex.pixels[3], tex.pixels[4], tex.pixels[5]);
	for (int i = start.x; i < end.x; i++) {
		for (int j = start.y; j < end.y; j++) {
			drawPixel(renderer, ivec2(i, j), tex.sample(
				vec2(i / double(end.x - start.x), j / double(end.y - start.y))
			) );
		}
	}
}

void threadedDrawTex(SDL_Renderer *renderer, const mippedTexture &tex, ivec2 start, ivec2 end) {
	if (start.x > end.x) swap(start.x, end.x);
	if (start.y > end.y) swap(start.y, end.y);
	const short threadCount = std::thread::hardware_concurrency();
	//If cores are even, render 2xN rectangles that fit the whole render section
	//If cores are odd, render 2xN rectangles that fit most of the render section,
	//with a vertical-ish rectangle, same size as rest, being the odd one out at the end.
	std::thread *renderThreads = new std::thread[threadCount];
	if (threadCount % 2) {
		//Haha just kidding no one has an odd number of threads
		//Ok nvm, just too lazy to code this right now
		///TODO: rendering a texture onto the screen with an odd number of threads
	} else {
		for (int i = 0; i < threadCount; i++) {
			if(i<(threadCount-2)){
				renderThreads[i] = std::thread(threadedDrawSection, std::ref(renderer), std::ref(tex),
										   start + ivec2((i % 2)*((end.y - start.y) / 2.0), (i / 2)*((end.y - start.y) / (threadCount / 2.0))),
										   start + ivec2((i % 2 + 1)*((end.y - start.y) / 2.0), (i / 2 + 1)*((end.y - start.y) / (threadCount / 2.0)))
			); } else {
				renderThreads[i] = std::thread(threadedDrawSection, std::ref(renderer), std::ref(tex),
											   start + ivec2((i % 2)*((end.y - start.y) / 2.0), (i / 2)*((end.y - start.y) / (threadCount / 2.0))),
											   end
				);
			}
		}
	}
	for (int i = 0; i < threadCount; i++) {
		renderThreads[i].join();
	}
	delete[] renderThreads;
	std::printf("\n\n\n\n");
}
*/