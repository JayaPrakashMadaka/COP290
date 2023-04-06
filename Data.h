#ifndef DATA_HPP
#define DATA_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib> 
#include <ctime>
using namespace std;

const char* SERVER_IP = "10.194.29.153";

const int LEVEL_WIDTH = 5120;
const int LEVEL_HEIGHT = 6144;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 100;

bool checkCollision( SDL_Rect a, SDL_Rect b );
bool check( SDL_Rect a , vector<SDL_Rect>& R ); 

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool check(SDL_Rect a , vector<SDL_Rect>& R){
	for(int i=0;i<R.size();i++){
		if(checkCollision(a,R[i])){
			return true;
		}
	}
	return false;
};


#endif
