#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <cmath>
#include <time.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <vector>
#include <cstdint>
#include <math.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "FpsCounter/FpsCounter.h"
#include "TableManager/TableManager.h"

using namespace std;

int main(int argc, char *argv[]) {
	srand(time(NULL)); //seed random number generator by time (used by chossing a random circle color)
    int windowHeight = 600;
    int windowWidth = 800;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
        cout << "Initialization failed" << endl;
    }

    SDL_Window *window = SDL_CreateWindow("Awesome satisfying drawing",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth,
            windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        SDL_Quit();
        return 2;
    }

    // We create a renderer with hardware acceleration, we also present according with the vertical sync refresh.
    SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;
	SDL_SetRenderDrawBlendMode(s, SDL_BLENDMODE_BLEND);

	FpsCounter fpsCounter = FpsCounter(SDL_GetTicks());
	const int fps_every = 60;
	int fps_calc_count = 0;


    bool quit = false;
    SDL_Event event;

	TableManager tableManager = TableManager(s);

	float baseSpeed = 0.0005;

	// setting up the default control circles
	// first param of add circle is speed, second is offset
	for (float i=1; i<15; i+=1) {
		tableManager.add_circle_x(baseSpeed*i, i*M_1_PI/4);
	}
	for (float i=1; i<10; i+=1.5) {
		tableManager.add_circle_y(baseSpeed*i, 0);
	}


	// main loop
	Uint32 last_frametime = SDL_GetTicks();
    while (!quit) {
		uint32_t ticks = SDL_GetTicks();
		Uint32 delta = ticks - last_frametime;
		last_frametime = ticks;

        fpsCounter.update(ticks);
		fps_calc_count++;
		if (fps_calc_count >= fps_every) {
			fps_calc_count = 0;
			cout << "FPS: "<< fpsCounter.fps << endl;
		}

		bool windowResized = false;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				windowResized = true;
				windowWidth = event.window.data1;
				windowHeight = event.window.data2;
			}
			if (event.key.type == SDL_KEYDOWN){
				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_F1:
						tableManager.showControlCircles = !tableManager.showControlCircles;
					case SDL_SCANCODE_F3:
						tableManager.showLines = !tableManager.showLines;
					default:;
				}
			}
        }

		SDL_SetRenderDrawColor(s, 41, 0, 0, 255);
        // We clear what we draw before
        SDL_RenderClear(s);

		tableManager.draw(delta, windowWidth, windowHeight, windowResized);
        // .. you could do some other drawing here
        // And now we present everything we draw after the clear.
        SDL_RenderPresent(s);
    }

    SDL_DestroyWindow(window);
    // We have to destroy the renderer, same as with the window.
    SDL_DestroyRenderer(s);
    SDL_Quit();

}
