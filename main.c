#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL2/include/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

#define true 1
#define false 0

#define WIDTH 640
#define HEIGHT 480

#define TIME_PER_FRAME 1.0 / 120.0

#define AXIS_MAX 32768

int main (int argc, char** argv) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Color white;

	SDL_Joystick* joystick;

	SDL_Rect dest;

	clock_t start;
	float elapsed;

	SDL_Event event;
	int quit = false;

	int x = 0, y = 0;

	char* text;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return EXIT_FAILURE;
	}
	if (TTF_Init() == -1) {
		fprintf(stderr, "Error initializing SDL_ttf.\n");
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow("SDL Test", 0, 0, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	font = TTF_OpenFont("courier-new.ttf", 64);

	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);

	white.r = white.g = white.b = white.a = 255;

	while (!quit) {
		start = clock();



		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawPoint(renderer, (WIDTH / 2) * (1.0 + ((float) x / (float) AXIS_MAX)), (HEIGHT / 2) * (1.0 + ((float) y / (float) AXIS_MAX)));

		SDL_RenderPresent(renderer);

		/*free(text);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);*/

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_JOYAXISMOTION:
					if (event.jaxis.axis == 0) {
						x = event.jaxis.value;
					} else if (event.jaxis.axis == 1) {
						y = event.jaxis.value;
					}
					break;
				case SDL_JOYBUTTONDOWN:
					if (event.jbutton.button == 2) {
						quit = true;
					}
				default:
					break;
			}
		}

		elapsed = (float) (clock() - start) / (float) CLOCKS_PER_SEC;
		if (elapsed < TIME_PER_FRAME) {
			SDL_Delay((TIME_PER_FRAME - elapsed) * 1000.0);
		}
	}

	/*SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);*/
	SDL_JoystickClose(joystick);

	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}
