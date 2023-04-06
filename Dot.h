#ifndef DOT_HPP
#define DOT_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <cstdlib> 
#include <ctime>
#include "LTexture.h"
#include "Data.h"
using namespace std;

class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 32;
		static const int DOT_HEIGHT = 32;

		//Maximum axis velocity of the dot
		 int DOT_VEL;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e ,  vector<SDL_Rect>& wall);


		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY , SDL_Renderer* gRenderer);

		//Position accessors
		int getPosX();
		int getPosY();
		int getdir();
		int getcount();
		SDL_Rect mCollider;
		int iscycle;
		int money;
		int bite;
		int count;
		int mPosX, mPosY;
		int direction;
		int imagecount;
		int music;
		int score;
};
LTexture gDotTexture;


//The sound effects that will be used
Mix_Chunk *gLow = NULL;

void Media()
{
	gLow = Mix_LoadWAV( "sounds/low.wav" );
	if( gLow == NULL )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}
}




Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 1920;
    DOT_VEL = 5;
    mCollider.w = DOT_WIDTH;
    mCollider.h = DOT_HEIGHT;
    direction=0;
    imagecount=0;
    iscycle = 0;
    count = 0;
    bite =0;
    score = 0;
    music = 0;
    money = 500;	
}

int f(int count){
	if(count% 15 ==0){
		return 10;
	}
	return 0;
} 
	
void Dot::handleEvent( SDL_Event& e , vector<SDL_Rect>& wall)
{
    //If a key was pressed
    	Media();	
	if( e.type == SDL_KEYDOWN ){
		int VEL = DOT_VEL + iscycle*DOT_VEL;
		music+=1;
		if( e.key.keysym.sym == SDLK_UP){
			   direction =1;
			   imagecount = (imagecount+1)%2;
			   count += 1;
			   money -= iscycle*f(count);
			   mPosY -= VEL;
			   mCollider.x = mPosX;
			   mCollider.y = mPosY;
			   for(int i=0;i<wall.size();i++){
    				if((mPosY < 0 ) ||(mPosY > LEVEL_HEIGHT) ||  checkCollision( mCollider, wall[i] )){
    					mPosY += VEL;
					mCollider.y = mPosY;
				}
    			  }
    		
    			  
    		}
            	else if (e.key.keysym.sym == SDLK_DOWN  ){
            		  direction = 3;
            		  imagecount = (imagecount+1)%2;
            		  count += 1;
            		  money -= iscycle*f(count);
            		  mPosY += VEL ;
            		  mCollider.x = mPosX;
			  mCollider.y = mPosY;
			  for(int i=0;i<wall.size();i++){
    				if((mPosY < 0 ) ||(mPosY > LEVEL_HEIGHT) ||  checkCollision( mCollider, wall[i] )){
    					mPosY -= VEL;
					mCollider.y = mPosY;
				}
    			  }
    			  
    		}
            	else if (e.key.keysym.sym == SDLK_LEFT  ){ 
            		direction = 2;
            		imagecount = (imagecount+1)%2; 
            		count += 1;
            		money -= iscycle*f(count);
            		mPosX -= VEL;
            		mCollider.x = mPosX;
			mCollider.y = mPosY;
            		for(int i=0;i<wall.size();i++){
    				if((mPosX < 0 ) ||(mPosX > LEVEL_WIDTH) ||  checkCollision( mCollider, wall[i] )){
    					mPosX += VEL;
					mCollider.x = mPosX;
				}
    			  }
    			
    		}
            	else if (e.key.keysym.sym == SDLK_RIGHT  ){
            		direction = 0;
            		imagecount = (imagecount+1)%2;
            		count += 1;
            		money -= iscycle*f(count);
            		mPosX += VEL;
            		mCollider.x = mPosX;
			mCollider.y = mPosY;
            		for(int i=0;i<wall.size();i++){
    				if((mPosX < 0 ) ||(mPosX > LEVEL_WIDTH) ||  checkCollision( mCollider, wall[i] )){
    					mPosX -= VEL;
					mCollider.x = mPosX;
				}
    			  }
    			
    		}
    		if(music % 10 ==0){
    			Mix_PlayChannel( -1,  gLow, 0 );
    		}
     }
}



void Dot::render( int camX, int camY , SDL_Renderer* gRenderer)
{
    //Show the dot relative to the camera
	gDotTexture.render( mPosX - camX, mPosY - camY ,gRenderer);
}

int Dot::getPosX()
{
	return mPosX;
}

int Dot::getPosY()
{
	return mPosY;
}

int Dot::getdir()
{
	return direction;
}

int Dot::getcount()
{
	return imagecount;
};

#endif

