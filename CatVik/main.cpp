//Made by Viktor Nikolaev Georgiev

#include "defines.h"

#include <iostream>
#include <SDL.h>

#include "ivec2.h"
#include "ivec3.h"
#include "vec2.h"
#include "vec3.h"

#include <thread>

#include "commonMath.h"
#include "commonDraw.h"
#include "textDrawing.h"
#include "mippedTexture.h"
#include "textureBaking.h"
#include "simpleTimer.h"

#include "pusheenCat.h"

#include "interactivePusheenMenu.h"
using namespace std;

//const int WX = 1280, WY = 720;


mippedTexture testTexture(4, 4);

pusheenCat testPusheen;

void initTestTexture() {
	testTexture.setPixel(ivec2(0, 0), vec3(0.2));
	testTexture.setPixel(ivec2(1, 0), vec3(1.0));
	testTexture.setPixel(ivec2(2, 0), vec3(0.0,1.0,0.0));
	testTexture.setPixel(ivec2(3, 0), vec3(0.0, 0.5, 0.0));

	testTexture.setPixel(ivec2(0, 1), vec3(0.0,0.0,1.0));
	testTexture.setPixel(ivec2(1, 1), vec3(1.0,0.0,0.0));
	testTexture.setPixel(ivec2(2, 1), vec3(0.0,1.0,1.0));
	testTexture.setPixel(ivec2(3, 1), vec3(0.5, 0.7, 0.2));

	testTexture.setPixel(ivec2(0, 2), vec3(1.0,1.0,0.0));
	testTexture.setPixel(ivec2(1, 2), vec3(0.2));
	testTexture.setPixel(ivec2(2, 2), vec3(1.0));
	testTexture.setPixel(ivec2(3, 2), vec3(1.0,0.2,1.0));

	testTexture.setPixel(ivec2(0, 3), vec3(1.9, 0.0, 1.0));
	testTexture.setPixel(ivec2(1, 3), vec3(0.3, 1.0, 0.0));
	testTexture.setPixel(ivec2(2, 3), vec3(0.0, 7.0, 1.0));
	testTexture.setPixel(ivec2(3, 3), vec3(0.5, 0.3, 0.9));
}

int main(int argc, char * argv[]) {
	
	int pusheenRes = 512;
	if (argc > 1){
		pusheenRes = atoi(argv[1]);
		cout << "Cat resolution: " << pusheenRes << endl; sleep_ms(1000);
	}
	mippedTexture pusheenTexture(pusheenRes, pusheenRes);
	simpleTimer timer;
	//bakeSection_obj<pusheenCat> (pusheenTexture, samplePusheen, 0, pusheenTexture.sizex*pusheenTexture.sizey, testPusheen);
	threadedBake<pusheenCat>(pusheenTexture, samplePusheen, testPusheen, thread::hardware_concurrency());

	//Multithreading WORKS! :D
	//Performance without MT: 3300ms
	//Performance with MT, 6 threads: 900ms (366%)
	//Other test: 657ms vs 2290ms (348%)
	//PassMark SingleThreadedPerformance (STP) of the CPU: 1407

	cout << "Time spent computing texture: " << timer.press() << "ms.\n";
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL Error! : " << SDL_GetError();
	}
	cout << "Available hardware threads: " << thread::hardware_concurrency()<<endl;

	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WX, WY, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	/*
	for (int i = 0; i < WY; i++) {
		drawPixel(renderer, ivec2(i), ivec3(
			int((i / double(WY)) * 256),
			0,
			256-int((i / double(WY)) * 256)
		) );
	}
	SDL_RenderPresent(renderer);
	Draws a diagonal colorful line...
	*/
	initTestTexture();
	//testTexture.wrapType = repeat;

	interactivePusheenMenu menuObj(&testPusheen, &pusheenTexture);
	thread menu(menuThread, &menuObj);
	while (menuObj.cursorPos!=-1) {

		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		//testTexture.interpType = constant;
		//threadedDrawTex(renderer, testTexture, ivec2(50, 50), ivec2(128));
		//drawTex(renderer, testTexture, ivec2(50), ivec2(50+128));
		//testTexture.interpType = linear;
		//drawTex(renderer, testTexture, ivec2(50+148, 50), ivec2(50+148+128,50+128));
		drawTex(renderer, pusheenTexture, ivec2(128), ivec2(128+pusheenRes));
		//threadedDrawTex(renderer, testTexture, ivec2(50+148, 50), ivec2(128));

		drawFPS(renderer, timer.press());


		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}



	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

