#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib> 
#include <ctime>
#include "LTexture.h"
#include "Data.h"
using namespace std;



class Enemy
{
	public:
		static const int ENEMY_WIDTH = 32;
		static const int ENEMY_HEIGHT = 32;
		static const int ENEMY_VEL = 5;
		
		Enemy();
		
		void move(SDL_Event& e , vector<SDL_Rect>& wall);
		
		void render(int camX, int camY , SDL_Renderer* gRenderer);
		
		int getePosX();
		int getePosY();
		int getedir();
		int getecount();
		SDL_Rect eCollider;
		int ePosX,ePosY;
		int edirection;
		int ecount;
};


LTexture eTexture;

Enemy::Enemy()
{
	ePosX = 64;
	ePosY = 1920;
	eCollider.w = ENEMY_WIDTH;
	eCollider.h = ENEMY_HEIGHT;
	edirection = 0;
	ecount = 0;
}

void Enemy::move(SDL_Event& e , vector<SDL_Rect>& wall)
{
	if( e.type == SDL_KEYDOWN || e.type == SDL_KEYUP ){
		srand(time(0));
		edirection = rand()%4;
		if(edirection == 0){
			ecount = (ecount+1)%2;
			ePosX += ENEMY_VEL;
			eCollider.x = ePosX;
			eCollider.y = ePosY;
			for(int i=0;i<wall.size();i++){
    				if((ePosX < 0 ) ||(ePosX > LEVEL_WIDTH) ||  checkCollision( eCollider, wall[i] ) ){
    					ePosX -= ENEMY_VEL;
					eCollider.x = ePosX;
				}
    			}
    		}
	    	else if (edirection == 1){
    			ecount = (ecount+1)%2;
    			ePosY -= ENEMY_VEL;
    			eCollider.x = ePosX;
    			eCollider.y = ePosY;
    			 for(int i=0;i<wall.size();i++){
    				if((ePosY < 0 ) ||(ePosY > LEVEL_HEIGHT) ||  checkCollision( eCollider, wall[i] ) ){
    					ePosY += ENEMY_VEL;
					eCollider.y = ePosY;
				}
    			}
    		}
	    	else if(edirection == 2){
	    		ecount = (ecount+1)%2;
	    		ePosX -= ENEMY_VEL;
	    		eCollider.x = ePosX;
	    		eCollider.y = ePosY;
	    		for(int i=0;i<wall.size();i++){
	    			if((ePosX < 0 ) ||(ePosX > LEVEL_WIDTH) ||  checkCollision( eCollider, wall[i] ) ){
	    				ePosX += ENEMY_VEL;
					eCollider.x = ePosX;
				}
	    		}
	    	}
	    	else if(edirection == 3){
	    		ecount = (ecount+1)%2;
	    		ePosY += ENEMY_VEL;
	    		eCollider.x = ePosX;
	    		eCollider.y = ePosY;
	    		 for(int i=0;i<wall.size();i++){
	    			if((ePosY < 0 ) ||(ePosY > LEVEL_HEIGHT) ||  checkCollision( eCollider, wall[i] ) ){
	    				ePosY -= ENEMY_VEL;
					eCollider.y = ePosY;
				}
	    		}
	    	}
	  }
}

void Enemy::render( int camX, int camY , SDL_Renderer* gRenderer)
{
    
	eTexture.render( ePosX - camX, ePosY - camY , gRenderer );
}

int Enemy::getePosX()
{
	return ePosX;
}
int Enemy::getePosY()
{
	return ePosY;
}
int Enemy::getedir()
{
	return edirection;
}
int Enemy::getecount()
{
	return ecount;
};


#endif
