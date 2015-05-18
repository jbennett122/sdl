//============================================================================
// Name        : fursy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <errno.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int SCREEN_BPP=32;

enum keyPressSurface{

	KEY_PRESS_DEFAULT,
	KEY_PRESS_UP,
	KEY_PRESS_DOWN,
	KEY_PRESS_LEFT,
	KEY_PRESS_RIGHT,
	KEY_PRESS_TOTAL


};

SDL_Surface* currentSurface=NULL;

SDL_Surface* keyPresses[KEY_PRESS_TOTAL];

//window
SDL_Surface* screen=NULL;

//background image
SDL_Surface* background=NULL;

//
SDL_Surface* crab=NULL;
SDL_Surface* dog=NULL;
SDL_Surface* image=NULL;

//event handler
SDL_Event event;

using namespace std;

//loads each image using path in local directory
SDL_Surface *load_image(std::string filename){

	//temporary storage for the image loaded
	SDL_Surface* loadedImage=NULL;

	//optimized image that will be used
	SDL_Surface* optimizedImage=NULL;

	//load the image
	loadedImage=IMG_Load(filename.c_str());

	printf("test");

	//if nothing went wrong
	if(loadedImage!=NULL){

		//create optimized image
		optimizedImage=SDL_DisplayFormat(loadedImage);

		//free old image
		SDL_FreeSurface(loadedImage);

		return optimizedImage;

	}else return NULL;



}


//two pointers one that points to where the background image is, the other to the window
//x y offset positions the image using rectangle object
void apply_surface(int x, int y, SDL_Surface* source,SDL_Surface* destination){

	//rectangle to hold offsets
	SDL_Rect offset;

	//offsets
	offset.x=x;
	offset.y=y;

	SDL_BlitSurface(source,NULL,destination,&offset);

}

bool init(){
	//initialize
		if(SDL_Init(SDL_INIT_EVERYTHING)==-1){

			cerr<<"initialization failed"<<endl;
			return false;

		}


		//set up screen
		screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);


		if(screen==NULL){

			cerr<<"screen is null"<<endl;
			return 1;
		}

		 //Set the window caption
		SDL_WM_SetCaption( "Event test", NULL );

		//If everything initialized fine
		return true;


}

bool load_files(){

	//load the image
	background=load_image("background.bmp");
		dog=load_image("dog.bmp");
		crab=load_image("crab.png");
	if((background||dog||crab)==0){

		return false;
	}

	return true;
}


bool load_media(){

	//success flag
	bool success = true;

	//default surface
	keyPresses[KEY_PRESS_DEFAULT] = load_image("04_key_presses/press.bmp");

	if(keyPresses[KEY_PRESS_DEFAULT]==NULL){

		printf("failed to display default image");
	}


	keyPresses[KEY_PRESS_UP] = load_image("04_key_presses/up.bmp");

	if(keyPresses[KEY_PRESS_UP]==NULL){

		printf("failed to display up image");
	}


	keyPresses[KEY_PRESS_DOWN] = load_image("04_key_presses/down.bmp");

	if(keyPresses[KEY_PRESS_DOWN]==NULL){

		printf("failed to display down image");
	}


	keyPresses[KEY_PRESS_LEFT] = load_image("04_key_presses/left.bmp");

	if(keyPresses[KEY_PRESS_LEFT]==NULL){

		printf("failed to display left image");
	}


	keyPresses[KEY_PRESS_RIGHT] = load_image("04_key_presses/right.bmp");

	if(keyPresses[KEY_PRESS_RIGHT]==NULL){

		printf("failed to display right image");
	}


}

void close(){



}

void cleanUp(){
SDL_FreeSurface(image);
SDL_Quit();
}



int main(int argc, char* argv[]) {

	//Quit bool
	bool quit = false;

	SDL_Event e;

	currentSurface = keyPresses[KEY_PRESS_DEFAULT];

	//initialize
	if(init()==false){

		return 1;
	}

	//load files
	if(load_files()==false){

		return 1;
	}


	//apply image to window starting at upper left corner


//apply_surface(0,0,background, screen);
//apply_surface(240,140,dog,screen);
//apply_surface(480,0,crab,screen);
SDL_BlitSurface(currentSurface,NULL,screen,NULL);
//SDL_UpdateWindowSurface();

	//Update the screen
	if( SDL_Flip( screen ) == -1 ) {
		return 1;
	}

	while(quit==false){

		while(SDL_PollEvent(&event)){

			if(event.type==SDL_QUIT){

				quit=true;
			}


				else if(e.type==SDL_KEYDOWN){

					//Select surfaces based on key press
					switch(e.key.keysym.sym){

					case SDLK_UP:
						currentSurface = keyPresses[KEY_PRESS_UP];


					case SDLK_DOWN:
						currentSurface = keyPresses[KEY_PRESS_DOWN];
					}


			}


		}
	}

	cleanUp();
	return 0;
}
