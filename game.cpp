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
#include "Enemy.h"
#include "Dot.h"
#include "map_window.cpp"
#include "position.cpp"
#include "task.cpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#define PORT 8080
using namespace std;

int sock = 0, valread;
sockaddr_in serv_addr;
pthread_t thread;
bool Terminate = false;
int pPosX = 0;
int pPosY = 0;
int pscore = 0;
bool display = false;

//Loads media
bool GloadMedia(SDL_Renderer* gRenderer);
//Scene textures

LTexture gBGTexture;

LTexture healthTexture;

LTexture MoneyTexture;

LTexture ScoreTexture;

LTexture ExitTexture;

LTexture PartnerTexture;

LTexture PScoreTexture;

void *getSignal(void *args){
    while(!Terminate){
    	char buffer[1024] ={0};
        valread = read(sock, buffer, 1024);
        string temp(buffer);
        string s(temp.begin(), temp.end());
         
         if (temp == "please_exit") {
            Terminate = true;
         }
         else{
         	for(int i =0;i<1024;i++){
         		if(buffer[i]==','){
         			for(int j=i+1 ;j<1024;j++){
         				if(buffer[j]==','){
         					string x(temp.begin(),temp.begin()+i);
         					string y(temp.begin()+i+1,temp.begin()+j);
         					string z(temp.begin()+j+1,temp.end());
         					if(x.size() < 5 and y.size() < 5 and z.size() < 4){
         						pPosX = stoi(x);
         						pPosY = stoi(y);
         						pscore = stoi(z);
         						display = true;
         					}
         				}
         			}
         		}
         	}
         }
    }
    return NULL;
}


Mix_Chunk *mDog = NULL;
Mix_Chunk *gMusic = NULL;
Mix_Chunk *gTask = NULL;
Mix_Chunk *gCoin = NULL;
Mix_Chunk *gHealth = NULL;
Mix_Chunk *gBell = NULL;

void gMedia(){
	mDog = Mix_LoadWAV( "sounds/dog.wav" );
	if( mDog == NULL )
	{
		printf( "Failed to laod dog sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		
	}
	gMusic = Mix_LoadWAV( "sounds/praising.wav" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	gTask = Mix_LoadWAV( "sounds/task.wav" );
	if( gTask == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	gCoin = Mix_LoadWAV( "sounds/coin.wav" );
	if( gCoin == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	gHealth = Mix_LoadWAV( "sounds/health.wav" );
	if( gHealth == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	gBell = Mix_LoadWAV( "sounds/bell.wav" );
	if( gBell == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	
}

bool GloadMedia(SDL_Renderer* gRenderer)
{
	bool success = true;
	//Load background texture
	if( !gBGTexture.loadFromFile( "Images/map.png" ,gRenderer))
	{ 
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !PartnerTexture.loadFromFile("Images/partner.png",gRenderer))
	{
		printf( "Failed to load partner texture!\n" );
		success = false;
	}

	return success;

}


int game(SDL_Renderer* gRenderer)
{
		gMedia();
    		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        		printf("\n Socket creation error \n");
        		return -1;
    		}
 
    		serv_addr.sin_family = AF_INET;
    		serv_addr.sin_port = htons(PORT);
 

    		if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr)<= 0) {
        		printf("\nInvalid address/ Address not supported \n");
        		return -1;
   	 	}
		if (connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))< 0) {
        		printf("\nConnection Failed \n");
        		return -1;
    		}
    		Terminate = false;
    		pthread_create(&thread, NULL, getSignal, NULL);
    		
		if( !GloadMedia(gRenderer) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{		
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;
			dot = setposition();
			Enemy e1;

			//The camera area
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			
			vector<SDL_Rect> wall;
			SDL_Rect wall1;
			wall1.x = 0;
			wall1.y = 1696;
			wall1.w = 768;
			wall1.h = 192;
			SDL_Rect wall2;
			wall2.x = 0;
			wall2.y = 1344;
			wall2.w = 768;
			wall2.h = 288;
			SDL_Rect wall3;
			wall3.x = 0;
			wall3.y = 1632;
			wall3.w = 736;
			wall3.h = 64;
			SDL_Rect wall4;
			wall4.x = 0;
			wall4.y = 0;
			wall4.w = 192;
			wall4.h = 1344;
			SDL_Rect wall5;
			wall5.x = 256;
			wall5.y = 1280;
			wall5.w = 512;
			wall5.h = 64;
			SDL_Rect wall6;
			wall6.x = 192;
			wall6.y = 704;
			wall6.w = 576;
			wall6.h = 448;
			SDL_Rect wall7;
			wall7.x = 192;
			wall7.y = 0;
			wall7.w = 192;
			wall7.h = 736;
			SDL_Rect wall8;
			wall8.x = 384;
			wall8.y = 0;
			wall8.w = 384;
			wall8.h = 96;
			SDL_Rect wall9;
			wall9.x = 512;
			wall9.y = 160;
			wall9.w = 256;
			wall9.h = 160;
			SDL_Rect wall10;
			wall10.x = 448;
			wall10.y = 384;
			wall10.w = 320;
			wall10.h = 256;
			SDL_Rect wall11;
			wall11.x = 448;
			wall11.y = 160;
			wall11.w = 64;
			wall11.h = 64;
			SDL_Rect wall12;
			wall12.x = 448;
			wall12.y = 288;
			wall12.w = 64;
			wall12.h = 32;
			SDL_Rect wall13;
			wall13.x = 0;
			wall13.y = 2016;
			wall13.w = 768;
			wall13.h = 576;
			SDL_Rect wall14;
			wall14.x = 0;
			wall14.y = 2592;
			wall14.w = 704;
			wall14.h = 672;
			SDL_Rect wall15;
			wall15.x = 896;
			wall15.y = 0;
			wall15.w = 3264;
			wall15.h = 96;
			SDL_Rect wall16;
			wall16.x = 896;
			wall16.y = 160;
			wall16.w = 320;
			wall16.h = 160;
			SDL_Rect wall17;
			wall17.x = 896;
			wall17.y = 384;
			wall17.w = 320;
			wall17.h = 256;
			SDL_Rect wall18;
			wall18.x = 896;
			wall18.y = 704;
			wall18.w = 3232;
			wall18.h = 640;
			SDL_Rect wall19;
			wall19.x = 896;
			wall19.y = 1344;
			wall19.w = 640;
			wall19.h = 224;
			SDL_Rect wall20;
			wall20.x = 896;
			wall20.y = 1568;
			wall20.w = 480;
			wall20.h = 128;
			SDL_Rect wall21;
			wall21.x = 896;
			wall21.y = 1696;
			wall21.w = 640;
			wall21.h = 192;
			SDL_Rect wall22;
			wall22.x = 704;
			wall22.y = 2720;
			wall22.w = 832;
			wall22.h = 544;
			SDL_Rect wall23;
			wall23.x = 1280;
			wall23.y = 160;
			wall23.w = 2880;
			wall23.h = 576;
			SDL_Rect wall24;
			wall24.x = 1664;
			wall24.y = 1344;
			wall24.w = 480;
			wall24.h = 416;
			SDL_Rect wall25;
			wall25.x = 1664;
			wall25.y = 1760;
			wall25.w = 224;
			wall25.h = 128;
			SDL_Rect wall26;
			wall26.x = 2016;
			wall26.y = 1760;
			wall26.w = 128;
			wall26.h = 128;
			SDL_Rect wall27;
			wall27.x = 2080;
			wall27.y = 1504;
			wall27.w = 64;
			wall27.h = 256;
			SDL_Rect wall28;
			wall28.x = 2144;
			wall28.y = 1408;
			wall28.w = 2016;
			wall28.h = 256;
			SDL_Rect wall29;
			wall29.x = 2208;
			wall29.y = 1664;
			wall29.w = 1952;
			wall29.h = 224;
			SDL_Rect wall30;
			wall30.x = 896;
			wall30.y = 2016;
			wall30.w = 640;
			wall30.h = 576;
			SDL_Rect wall31;
			wall31.x = 2080;
			wall31.y = 160;
			wall31.w = 2080;
			wall31.h = 1504;
			SDL_Rect wall32;
			wall32.x = 1664;
			wall32.y = 2016;
			wall32.w = 480;
			wall32.h = 256;
			SDL_Rect wall33;
			wall33.x = 2208;
			wall33.y = 2016;
			wall33.w = 288;
			wall33.h = 576;
			SDL_Rect wall34;
			wall34.x = 1664;
			wall34.y = 2336;
			wall34.w = 480;
			wall34.h = 256;
			SDL_Rect wall35;
			wall35.x = 1856;
			wall35.y = 2080;
			wall35.w = 640;
			wall35.h = 448;
			SDL_Rect wall36;
			wall36.x = 2624;
			wall36.y = 2016;
			wall36.w = 480;
			wall36.h = 96;
			SDL_Rect wall37;
			wall37.x = 2656;
			wall37.y = 2112;
			wall37.w = 448;
			wall37.h = 64;
			SDL_Rect wall38;
			wall38.x = 2752;
			wall38.y = 2176;
			wall38.w = 352;
			wall38.h = 384;
			SDL_Rect wall39;
			wall39.x = 2656;
			wall39.y = 2240;
			wall39.w = 96;
			wall39.h = 320;
			SDL_Rect wall40;
			wall40.x = 2624;
			wall40.y = 2240;
			wall40.w = 32;
			wall40.h = 32;
			SDL_Rect wall41;
			wall41.x = 2624;
			wall41.y = 2336;
			wall41.w = 32;
			wall41.h = 256;
			SDL_Rect wall42;
			wall42.x = 2720;
			wall42.y = 2560;
			wall42.w = 256;
			wall42.h = 32;
			SDL_Rect wall43;
			wall43.x = 3040;
			wall43.y = 2560;
			wall43.w = 64;
			wall43.h = 32;
			SDL_Rect wall44;
			wall44.x = 1664;
			wall44.y = 2720;
			wall44.w = 416;
			wall44.h = 1568;
			SDL_Rect wall45;
			wall45.x = 2080;
			wall45.y = 2752;
			wall45.w = 640;
			wall45.h = 512;
			SDL_Rect wall46;
			wall46.x = 2144;
			wall46.y = 2720;
			wall46.w = 576;
			wall46.h = 32;
			SDL_Rect wall47;
			wall47.x = 2784;
			wall47.y = 2720;
			wall47.w = 384;
			wall47.h = 352;
			SDL_Rect wall48;
			wall48.x = 3168;
			wall48.y = 2720;
			wall48.w = 32;
			wall48.h = 256;
			SDL_Rect wall49;
			wall49.x = 3168;
			wall49.y = 3040;
			wall49.w = 32;
			wall49.h = 32;
			SDL_Rect wall50;
			wall50.x = 2720;
			wall50.y = 3136;
			wall50.w = 480;
			wall50.h = 128;
			SDL_Rect wall51;
			wall51.x = 3328;
			wall51.y = 1888;
			wall51.w = 832;
			wall51.h = 1696;
			SDL_Rect wall52;
			wall52.x = 3328;
			wall52.y = 3712;
			wall52.w = 512;
			wall52.h = 736;
			SDL_Rect wall53;
			wall53.x = 3840;
			wall53.y = 3712;
			wall53.w = 128;
			wall53.h = 192;
			SDL_Rect wall54;
			wall54.x = 3850;
			wall54.y = 3904;
			wall54.w = 64;
			wall54.h = 416;
			SDL_Rect wall55;
			wall55.x = 4032;
			wall55.y = 3712;
			wall55.w = 160;
			wall55.h = 192;
			SDL_Rect wall56;
			wall56.x = 3904;
			wall56.y = 3968;
			wall56.w = 288;
			wall56.h = 480;
			SDL_Rect wall57;
			wall57.x = 4256;
			wall57.y = 3968;
			wall57.w = 384;
			wall57.h = 480;
			SDL_Rect wall58;
			wall58.x = 4256;
			wall58.y = 3712;
			wall58.w = 384;
			wall58.h = 192;
			SDL_Rect wall59;
			wall59.x = 4288;
			wall59.y = 3904;
			wall59.w = 352;
			wall59.h = 64;
			SDL_Rect wall60;
			wall60.x = 2176;
			wall60.y = 5184;
			wall60.w = 352;
			wall60.h = 384;
			SDL_Rect wall61;
			wall61.x = 2528;
			wall61.y = 5216;
			wall61.w = 64;
			wall61.h = 352;
			SDL_Rect wall62;
			wall62.x = 2592;
			wall62.y = 5184;
			wall62.w = 320;
			wall62.h = 384;
			SDL_Rect wall63;
			wall63.x = 3168;
			wall63.y = 5216;
			wall63.w = 64;
			wall63.h = 352;
			SDL_Rect wall64;
			wall64.x = 3232;
			wall64.y = 5184;
			wall64.w = 96;
			wall64.h = 384;
			SDL_Rect wall65;
			wall65.x = 2976;
			wall65.y = 5184;
			wall65.w = 192;
			wall65.h = 384;
			SDL_Rect wall66;
			wall66.x = 2912;
			wall66.y = 5216;
			wall66.w = 64;
			wall66.h = 352;
			SDL_Rect wall67;
			wall67.x = 1472;
			wall67.y = 5184;
			wall67.w = 576;
			wall67.h = 384;
			SDL_Rect wall68;
			wall68.x = 2016;
			wall68.y = 5536;
			wall68.w = 192;
			wall68.h = 32;
			SDL_Rect wall69;
			wall69.x = 3232;
			wall69.y = 1984;
			wall69.w = 96;
			wall69.h = 32;
			SDL_Rect wall70;
			wall70.x = 3328;
			wall70.y = 5216;
			wall70.w = 1024;
			wall70.h = 320;
			SDL_Rect wall71;
			wall71.x = 3392;
			wall71.y = 5184;
			wall71.w = 320;
			wall71.h = 32;
			SDL_Rect wall72;
			wall72.x = 3776;
			wall72.y = 5184;
			wall72.w = 352;
			wall72.h = 32;
			SDL_Rect wall73;
			wall73.x = 4192;
			wall73.y = 5184;
			wall73.w = 160;
			wall73.h = 32;
			SDL_Rect wall74;
			wall74.x = 4032;
			wall74.y = 5536;
			wall74.w = 288;
			wall74.h = 608;
			SDL_Rect wall75;
			wall75.x = 4320;
			wall75.y = 5600;
			wall75.w = 32;
			wall75.h = 192;
			SDL_Rect wall76;
			wall76.x = 4320;
			wall76.y = 5856;
			wall76.w = 32;
			wall76.h = 288;
			SDL_Rect wall77;
			wall77.x = 4512;
			wall77.y = 5216;
			wall77.w = 544;
			wall77.h = 928;
			SDL_Rect wall78;
			wall78.x = 4480;
			wall78.y = 5184;
			wall78.w = 480;
			wall78.h = 32;
			SDL_Rect wall79;
			wall79.x = 4480;
			wall79.y = 5216;
			wall79.w = 32;
			wall79.h = 320;
			SDL_Rect wall80;
			wall80.x = 4480;
			wall80.y = 5600;
			wall80.w = 32;
			wall80.h = 192;
			SDL_Rect wall81;
			wall81.x = 4480;
			wall81.y = 5856;
			wall81.w = 32;
			wall81.h = 288;
			SDL_Rect wall82;
			wall82.x = 3968;
			wall82.y = 3712;
			wall82.w = 64;
			wall82.h = 32;
			SDL_Rect wall83;
			wall83.x = 4192;
			wall83.y = 3712;
			wall83.w = 64;
			wall83.h = 32;
			SDL_Rect wall84;
			wall84.x = 1472;
			wall84.y = 4352;
			wall84.w = 576;
			wall84.h = 608;
			SDL_Rect wall85;
			wall85.x = 1472;
			wall85.y = 4960;
			wall85.w = 480;
			wall85.h = 64;
			SDL_Rect wall86;
			wall86.x = 1472;
			wall86.y = 5024;
			wall86.w = 576;
			wall86.h = 32;
			SDL_Rect wall87;
			wall87.x = 2176;
			wall87.y = 4576;
			wall87.w = 384;
			wall87.h = 480;
			SDL_Rect wall88;
			wall88.x = 2560;
			wall88.y = 4608;
			wall88.w = 224;
			wall88.h = 448;
			SDL_Rect wall89;
			wall89.x = 2624;
			wall89.y = 4576;
			wall89.w = 160;
			wall89.h = 32;
			SDL_Rect wall90;
			wall90.x = 2848;
			wall90.y = 4576;
			wall90.w = 352;
			wall90.h = 192;
			SDL_Rect wall91;
			wall91.x = 2880;
			wall91.y = 4768;
			wall91.w = 320;
			wall91.h = 224;
			SDL_Rect wall92;
			wall92.x = 2976;
			wall92.y = 4992;
			wall92.w = 224;
			wall92.h = 64;
			SDL_Rect wall93;
			wall93.x = 2752;
			wall93.y = 4864;
			wall93.w = 160;
			wall93.h = 192;
			SDL_Rect wall94;
			wall94.x = 3328;
			wall94.y = 4576;
			wall94.w = 448;
			wall94.h = 480;
			SDL_Rect wall95;
			wall95.x = 3904;
			wall95.y = 4512;
			wall95.w = 448;
			wall95.h = 512;
			SDL_Rect wall96;
			wall96.x = 3904;
			wall96.y = 5024;
			wall96.w = 224;
			wall96.h = 32;
			SDL_Rect wall97;
			wall97.x = 4192;
			wall97.y = 5024;
			wall97.w = 160;
			wall97.h = 32;
			SDL_Rect wall98;
			wall98.x = 4480;
			wall98.y = 4576;
			wall98.w = 160;
			wall98.h = 480;
			SDL_Rect wall99;
			wall99.x = 4768;
			wall99.y = 3584;
			wall99.w = 288;
			wall99.h = 320;
			SDL_Rect wall100;
			wall100.x = 4768;
			wall100.y = 3904;
			wall100.w = 128;
			wall100.h = 1152;
			SDL_Rect wall101;
			wall101.x = 5024;
			wall101.y = 3584;
			wall101.w = 32;
			wall101.h = 2560;
			SDL_Rect wall102;
			wall102.x = 4288;
			wall102.y = 0;
			wall102.w = 224;
			wall102.h = 3584;
			SDL_Rect wall103;
			wall103.x = 1504;
			wall103.y = 2848;
			wall103.w = 800;
			wall103.h = 1408;
			SDL_Rect wall104;
			wall104.x = 2304;
			wall104.y = 3488;
			wall104.w = 64;
			wall104.h = 960;
			SDL_Rect wall105;
			wall105.x = 2272;
			wall105.y = 3072;
			wall105.w = 224;
			wall105.h = 352;
			SDL_Rect wall106;
			wall106.x = 2560;
			wall106.y = 3328;
			wall106.w = 576;
			wall106.h = 256;
			SDL_Rect wall107;
			wall107.x = 2432;
			wall107.y = 3488;
			wall107.w = 128;
			wall107.h = 96;
			SDL_Rect wall108;
			wall108.x = 3136;
			wall108.y = 3328;
			wall108.w = 64;
			wall108.h = 192;
			SDL_Rect wall109;
			wall109.x = 2432;
			wall109.y = 3744;
			wall109.w = 768;
			wall109.h = 640;
			SDL_Rect wall110;
			wall110.x = 2432;
			wall110.y = 4384;
			wall110.w = 192;
			wall110.h = 64;
			SDL_Rect wall111;
			wall111.x = 2688;
			wall111.y = 4384;
			wall111.w = 256;
			wall111.h = 64;
			SDL_Rect wall112;
			wall112.x = 3008;
			wall112.y = 4384;
			wall112.w = 192;
			wall112.h = 64;
			SDL_Rect wall113;
			wall113.x = 2432;
			wall113.y = 3712;
			wall113.w = 352;
			wall113.h = 32;
			SDL_Rect wall114;
			wall114.x = 2848;
			wall114.y = 3712;
			wall114.w = 64;
			wall114.h = 32;
			SDL_Rect wall115;
			wall115.x = 2976;
			wall115.y = 3712;
			wall115.w = 224;
			wall115.h = 32;
			
			
			
			
			
			wall.push_back(wall1);
			wall.push_back(wall2);
			wall.push_back(wall3);
			wall.push_back(wall4);
			wall.push_back(wall5);
			wall.push_back(wall6);
			wall.push_back(wall7);
			wall.push_back(wall8);
			wall.push_back(wall9);
			wall.push_back(wall10);
			wall.push_back(wall11);
			wall.push_back(wall12);
			wall.push_back(wall13);
			wall.push_back(wall14);
			wall.push_back(wall15);
			wall.push_back(wall16);
			wall.push_back(wall17);
			wall.push_back(wall18);
			wall.push_back(wall19);
			wall.push_back(wall20);
			wall.push_back(wall21);
			wall.push_back(wall22);
			wall.push_back(wall23);
			wall.push_back(wall24);
			wall.push_back(wall25);
			wall.push_back(wall26);
			wall.push_back(wall27);
			wall.push_back(wall28);
			wall.push_back(wall29);
			wall.push_back(wall30);
			wall.push_back(wall31);
			wall.push_back(wall32);
			wall.push_back(wall33);
			wall.push_back(wall34);
			wall.push_back(wall35);
			wall.push_back(wall36);
			wall.push_back(wall37);
			wall.push_back(wall38);
			wall.push_back(wall39);
			wall.push_back(wall40);
			wall.push_back(wall41);
			wall.push_back(wall42);
			wall.push_back(wall43);
			wall.push_back(wall44);
			wall.push_back(wall45);
			wall.push_back(wall46);
			wall.push_back(wall47);
			wall.push_back(wall48);
			wall.push_back(wall49);
			wall.push_back(wall50);
			wall.push_back(wall51);
			wall.push_back(wall52);
			wall.push_back(wall53);
			wall.push_back(wall54);
			wall.push_back(wall55);
			wall.push_back(wall56);
			wall.push_back(wall57);
			wall.push_back(wall58);
			wall.push_back(wall59);
			wall.push_back(wall60);
			wall.push_back(wall61);
			wall.push_back(wall62);
			wall.push_back(wall63);
			wall.push_back(wall64);
			wall.push_back(wall65);
			wall.push_back(wall66);
			wall.push_back(wall67);
			wall.push_back(wall68);
			wall.push_back(wall69);
			wall.push_back(wall70);
			wall.push_back(wall71);
			wall.push_back(wall72);
			wall.push_back(wall73);
			wall.push_back(wall74);
			wall.push_back(wall75);
			wall.push_back(wall76);
			wall.push_back(wall77);
			wall.push_back(wall78);
			wall.push_back(wall79);
			wall.push_back(wall80);
			wall.push_back(wall81);
			wall.push_back(wall82);
			wall.push_back(wall83);
			wall.push_back(wall84);
			wall.push_back(wall85);
			wall.push_back(wall86);
			wall.push_back(wall87);
			wall.push_back(wall88);
			wall.push_back(wall89);
			wall.push_back(wall90);
			wall.push_back(wall91);
			wall.push_back(wall92);
			wall.push_back(wall93);
			wall.push_back(wall94);
			wall.push_back(wall95);
			wall.push_back(wall96);
			wall.push_back(wall97);
			wall.push_back(wall98);
			wall.push_back(wall99);
			wall.push_back(wall100);
			wall.push_back(wall101);
			wall.push_back(wall102);
			wall.push_back(wall103);
			wall.push_back(wall104);
			wall.push_back(wall105);
			wall.push_back(wall106);
			wall.push_back(wall107);
			wall.push_back(wall108);
			wall.push_back(wall109);
			wall.push_back(wall110);
			wall.push_back(wall111);
			wall.push_back(wall112);
			wall.push_back(wall113);
			wall.push_back(wall114);
			wall.push_back(wall115);
			
			SDL_Rect Hosp;
			Hosp.x = 3136;
			Hosp.y = 3520;
			Hosp.w = 64;
			Hosp.h = 64;
			
			vector<SDL_Rect> yulu;
			
			SDL_Rect yulu1;
			yulu1.x = 288;
			yulu1.y = 1952;
			yulu1.w = 128;
			yulu1.h = 64;
			
			SDL_Rect yulu2;
			yulu2.x = 1600;
			yulu2.y = 1760;
			yulu2.w = 64;
			yulu2.h = 128;
			
			SDL_Rect yulu3;
			yulu3.x = 448;
			yulu3.y = 1216;
			yulu3.w = 128;
			yulu3.h = 64;
			
			SDL_Rect yulu4;
			yulu4.x = 2720;
			yulu4.y = 2912;
			yulu4.w = 64;
			yulu4.h = 128;
			
			SDL_Rect yulu5;
			yulu5.x = 2496;
			yulu5.y = 3360;
			yulu5.w = 64;
			yulu5.h = 128;
			
			SDL_Rect yulu6;
			yulu6.x = 3264;
			yulu6.y = 3456;
			yulu6.w = 64;
			yulu6.h = 128;
			
			SDL_Rect yulu7;
			yulu7.x = 3840;
			yulu7.y = 4512;
			yulu7.w = 64;
			yulu7.h = 128;
			
			SDL_Rect yulu8;
			yulu8.x = 4416;
			yulu8.y = 5184;
			yulu8.w = 64;
			yulu8.h = 128;
			
			yulu.push_back(yulu1);
			yulu.push_back(yulu2);
			yulu.push_back(yulu3);
			yulu.push_back(yulu4);
			yulu.push_back(yulu5);
			yulu.push_back(yulu6);
			yulu.push_back(yulu7);
			yulu.push_back(yulu8);
			
			SDL_Rect SBI;
			SBI.x = 1376;
			SBI.y = 1568;
			SBI.w = 128;
			SBI.h = 128;
			
			
			Enemy e2;
			e2.ePosX = 768;
			e2.ePosY = 1440;
			Enemy e3;
			e3.ePosX = 1536;
			e3.ePosY = 2656;
			Enemy e4;
			e4.ePosX = 768;
			e4.ePosY = 2240;
			Enemy e5;
			e5.ePosX = 2784;
			e5.ePosY = 2688;
			Enemy e6;
			e6.ePosX = 3200;
			e6.ePosY = 4384;
			Enemy e7;
			e7.ePosX = 4352;
			e7.ePosY = 5440;
			Enemy e8;
			e8.ePosX = 4640;
			e8.ePosY = 5120;
			
			SDL_Rect LHC;
			LHC.x = 1536;
			LHC.y = 1344;
			LHC.w = 128;
			LHC.h = 64;
			
			SDL_Rect MasalaMix;
			MasalaMix.x = 2784;
			MasalaMix.y = 3648;
			MasalaMix.w = 192;
			MasalaMix.h = 96;
			
			SDL_Rect Himadri;
			Himadri.x = 192;
			Himadri.y = 1280;
			Himadri.w = 64;
			Himadri.h = 64;
			
			SDL_Rect Volleyball;
			Volleyball.x = 2560;
			Volleyball.y = 4544;
			Volleyball.w = 64;
			Volleyball.h = 64;
			
			SDL_Rect Library;
			Library.x = 2624;
			Library.y = 2176;
			Library.w = 128;
			Library.h = 64;
			
			while( !quit )
			{
					string s;
					s = to_string(dot.mPosX)+","+to_string(dot.mPosY)+","+to_string(dot.score);
        				const char* hello = s.c_str();
         				send(sock, hello, strlen(hello), 0);
				if(dot.DOT_VEL <= 0 || dot.score == 600){
				
					string x;
					x = "please_exit";
        				const char* hello = x.c_str();
         				send(sock, hello, strlen(hello), 0);
         				quit = true;
				} 
				if(checkCollision(dot.mCollider , e1.eCollider) or checkCollision(dot.mCollider , e2.eCollider) or checkCollision(dot.mCollider , e3.eCollider) or checkCollision(dot.mCollider , e4.eCollider) or checkCollision(dot.mCollider , e5.eCollider) or checkCollision(dot.mCollider , e6.eCollider) or checkCollision(dot.mCollider , e7.eCollider)or checkCollision(dot.mCollider , e8.eCollider)){
						dot.bite+=1;
						if(dot.bite > 10 and dot.bite % 20 ==0 ){
							dot.DOT_VEL -= 1;
							cout<<"dog-bite"<<"\n";
							Mix_PlayChannel( -1,  mDog , 0 );
						}
				}
				if (dot.money == 0){
					dot.iscycle =0;
				}
				
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						
						string x;
						x = "please_exit";
        					const char* hello = x.c_str();
         					send(sock, hello, strlen(hello), 0);
         					quit = true;
					}
					else if(e.type == SDL_KEYDOWN and  e.key.keysym.sym == SDLK_m){
						getmap(dot);
					}
					else if(e.type == SDL_KEYDOWN and  e.key.keysym.sym == SDLK_t){
						getTask(dot);
					}
					else if(checkCollision(dot.mCollider , Hosp) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0){
							dot.DOT_VEL = 5;
							Mix_PlayChannel( -1,  gHealth , 0 );
					}
					else if(checkCollision(dot.mCollider,SBI) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0){
							dot.money = 500;
							Mix_PlayChannel( -1,  gCoin , 0 );
					}
					else if(check(dot.mCollider , yulu) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0){
						if(dot.iscycle == 1){
							dot.iscycle = 0;
						}
						else if (dot.iscycle == 0 and dot.money > 0){
							dot.count = 0;
							dot.iscycle =1;
							Mix_PlayChannel( -1,  gBell , 0 );
						}
					}
					else if(checkCollision(dot.mCollider,LHC) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0 and dot.score == 0){
							dot.score+=100;
							Mix_PlayChannel( -1,  gTask , 0 );
					}
					else if(checkCollision(dot.mCollider,MasalaMix) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0 and dot.score == 100){
							dot.score+=100;
							Mix_PlayChannel( -1,  gTask , 0 );
					}
					else if(checkCollision(dot.mCollider,Himadri) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0 and dot.score == 200){
							dot.score+=100;
							Mix_PlayChannel( -1,  gTask , 0 );
					}
					else if(checkCollision(dot.mCollider,Volleyball) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0 and dot.score == 300){
							dot.score+=100;
							Mix_PlayChannel( -1,  gTask , 0 );
					}
					else if(checkCollision(dot.mCollider,Library) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0 and dot.score == 400){
							dot.score+=100;
							Mix_PlayChannel( -1,  gTask , 0 );
					}
					else if(checkCollision(dot.mCollider,Himadri) and e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0 and dot.score == 500){
							dot.score+=100;
							Mix_PlayChannel( -1,  gTask , 0 );
					}
					
				}
				gDotTexture.MyLoad("man/dot",dot.iscycle,dot.getdir(),dot.getcount(),gRenderer);
				eTexture.MyLoad("dog/dog",0,e1.getedir(),e1.getecount() , gRenderer);
				healthTexture.HLoad(abs(dot.DOT_VEL), gRenderer);
				MoneyTexture.Load("money/money",dot.money,gRenderer);
				ScoreTexture.Load("Images/score",dot.score,gRenderer);
				PScoreTexture.Load("Images/score",pscore,gRenderer);
				e1.move(e , wall);
				e2.move(e , wall);
				e3.move(e , wall);
				e4.move(e , wall);
				e5.move(e , wall);
				e6.move(e , wall);
				e7.move(e , wall);
				e8.move(e , wall);
				dot.handleEvent( e , wall);
				
				
				//Center the camera over the dot
				camera.x = ( dot.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
				camera.y = ( dot.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

				//Keep the camera in bounds
				if( camera.x < 0 )
				{ 
					camera.x = 0;
				}
				if( camera.y < 0 )
				{
					camera.y = 0;
				}
				if( camera.x > LEVEL_WIDTH - camera.w )
				{
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if( camera.y > LEVEL_HEIGHT - camera.h )
				{
					camera.y = LEVEL_HEIGHT - camera.h;
				}

				//Render background
				gBGTexture.render( 0, 0 ,gRenderer, &camera);
				
				healthTexture.render(32,32,gRenderer);
				MoneyTexture.render(32,96,gRenderer);
				ScoreTexture.render(1632,32,gRenderer);
				if(display){
					PScoreTexture.render(1632,96,gRenderer);
				}
				PartnerTexture.render(pPosX - camera.x , pPosY - camera.y , gRenderer);

				//Render objects
				dot.render( camera.x, camera.y,gRenderer );
				
				
				e1.render(camera.x, camera.y ,gRenderer);
				e2.render(camera.x, camera.y ,gRenderer);
				e3.render(camera.x, camera.y ,gRenderer);
				e4.render(camera.x, camera.y ,gRenderer);
				e5.render(camera.x, camera.y ,gRenderer);
				e6.render(camera.x, camera.y ,gRenderer);
				e7.render(camera.x, camera.y ,gRenderer);
				e8.render(camera.x, camera.y ,gRenderer);

				//Update screen
				SDL_RenderPresent( gRenderer );
	
		
			
	 }
	 	
	
			bool quit1 = false;
			SDL_Event s;
			int music = 0;
			while(!quit1){
			
				while( SDL_PollEvent( &s ) != 0 )
				{
					//User requests quit
					if( s.type == SDL_QUIT )
					{
						quit1 = true;
					}
				}
				ExitTexture.Load("Images/scorecard",dot.score,gRenderer);
				ExitTexture.render( 0, 0 ,gRenderer);	
				SDL_RenderPresent( gRenderer );
				if(music == 0){
					Mix_PlayChannel( -1,  gMusic , 0 );
					music+=1;
				}	
			}
			
	}
	return 0;
}
