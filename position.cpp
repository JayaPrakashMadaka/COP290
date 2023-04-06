#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib> 
#include <ctime>
#include "LTexture.h"
#include "Data.h"
#include "Enemy.h"
#include "Dot.h"
using namespace std;

SDL_Window* gPWindow = NULL;


//The window renderer
SDL_Renderer* gPRenderer = NULL;

LTexture PositionTexture;

Dot setposition()
{
	Dot dot;
	bool quit = false;
	SDL_Event e;
	gPWindow = SDL_CreateWindow( "CHOOSE HOSTEL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED );
	gPRenderer = SDL_CreateRenderer( gPWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_SetRenderDrawColor( gPRenderer, 0, 0, 0, 0);
	while(!quit){
		while(SDL_PollEvent( &e) != 0)
		{
			if(e.type == SDL_KEYDOWN )
			{
				if( e.key.keysym.sym == SDLK_g){
					dot.mPosX = 0;
					dot.mPosY = 1920;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_1){
					dot.mPosX = 3328;
					dot.mPosY = 5184;
					dot.direction = 1;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_2){
					dot.mPosX = 3712;
					dot.mPosY = 5184;
					dot.direction = 1;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_3){
					dot.mPosX = 2912;
					dot.mPosY = 5184;
					dot.direction = 1;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_4){
					dot.mPosX = 2528;
					dot.mPosY = 5184;
					dot.direction = 1;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_5){
					dot.mPosX = 2624;
					dot.mPosY = 4384;
					dot.direction = 3;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_6){
					dot.mPosX = 2944;
					dot.mPosY = 4384;
					dot.direction = 3;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_7){
					dot.mPosX = 1952;
					dot.mPosY = 4960;
					dot.direction = 0;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_8){
					dot.mPosX = 2496;
					dot.mPosY = 3328;
					dot.direction = 3;
					quit = true;
				}
				else if( e.key.keysym.sym == SDLK_9){
					dot.mPosX = 2304;
					dot.mPosY = 3424;
					dot.direction = 0;
					quit = true;
				}
				else {
					quit = true;
				}
			}
		}
		MapTexture.loadFromFile("Images/position.png",gPRenderer);
		SDL_RenderClear( gPRenderer );
		MapTexture.render(0,0,gPRenderer);
		SDL_RenderPresent( gPRenderer );
	}
	PositionTexture.free();
	SDL_DestroyRenderer( gPRenderer );
	SDL_DestroyWindow( gPWindow);
	gMWindow = NULL;
	gMRenderer = NULL;
	return dot;
}
