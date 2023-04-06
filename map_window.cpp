#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib> 
#include <ctime>
#include "LTexture.h"
#include "Data.h"
#include "Dot.h"
using namespace std;

SDL_Window* gMWindow = NULL;


//The window renderer
SDL_Renderer* gMRenderer = NULL;



LTexture MapTexture;

LTexture MarkTexture;


void getmap(Dot dot){
	bool quit2 = false;
	SDL_Event s1;
	gMWindow = SDL_CreateWindow( "IITD MAP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED );
	gMRenderer = SDL_CreateRenderer( gMWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_SetRenderDrawColor( gMRenderer, 0, 0, 0, 0);
	while(!quit2){
		while(SDL_PollEvent( &s1) != 0)
		{
			if(s1.type == SDL_KEYDOWN and s1.key.keysym.sym == SDLK_ESCAPE)
			{
				quit2 = true;
			}
		}
		MapTexture.loadFromFile("Images/getmap.png",gMRenderer);
		MarkTexture.loadFromFile("Images/mark.png",gMRenderer);
		SDL_RenderClear( gMRenderer );
		MapTexture.render(0,0,gMRenderer);
		int x = static_cast<int>(dot.getPosX()*0.375);
		int y = static_cast<int>(dot.getPosY()*0.17578125);
		MarkTexture.render(x,y,gMRenderer);
		SDL_RenderPresent( gMRenderer );
	}
	MapTexture.free();
	MarkTexture.free();
	SDL_DestroyRenderer( gMRenderer );
	SDL_DestroyWindow( gMWindow);
	gMWindow = NULL;
	gMRenderer = NULL;
}
