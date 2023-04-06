#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib> 
#include <ctime>
#include "LTexture.h"

using namespace std;

SDL_Window* gTWindow = NULL;


//The window renderer
SDL_Renderer* gTRenderer = NULL;

void getTask(Dot dot){
	bool quit = false;
	SDL_Event e;
	gTWindow = SDL_CreateWindow( "TASKS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED );
	gTRenderer = SDL_CreateRenderer( gTWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_SetRenderDrawColor( gTRenderer, 0, 0, 0, 0);
	while(!quit){
		while(SDL_PollEvent( &e) != 0)
		{
			if(e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}
		MapTexture.Load("Images/task",dot.score,gTRenderer);
		SDL_RenderClear( gTRenderer );
		MapTexture.render(0,0,gTRenderer);
		SDL_RenderPresent( gTRenderer );
	}
	MapTexture.free();
	SDL_DestroyRenderer( gTRenderer );
	SDL_DestroyWindow( gTWindow);
	gTWindow = NULL;
	gTRenderer = NULL;

}
