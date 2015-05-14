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

	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL


};


SDL_Surface* background=NULL;
SDL_Surface* screen=NULL;
SDL_Surface* message=NULL;
SDL_Surface* image=NULL;

SDL_Event event;

using namespace std;


SDL_Surface *load_image(std::string filename){

	//temporary storage for the image loaded
	SDL_Surface* loadedImage=NULL;

	//optimized image that will be used
	SDL_Surface* optimizedImage=NULL;

	//load the image
	loadedImage=IMG_Load(filename.c_str());

	//if nothing went wrong
	if(loadedImage!=NULL){

		//create optimized image
		optimizedImage=SDL_DisplayFormat(loadedImage);

		//free old image
		SDL_FreeSurface(loadedImage);

		return optimizedImage;

	}else return NULL;



}

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
	image=load_image("x.png");

	if(image==NULL){

		return false;
	}

	return true;
}

void cleanUp(){

	SDL_FreeSurface(image);
	SDL_Quit();

}

int main(int argc, char* argv[]) {

	//Quit bool
	bool quit = false;

	//initialize
	if(init()==false){

		return 1;
	}

	//load files
	if(load_files()==false){

		return 1;
	}

	//apply image to screen
	apply_surface(0,0,image, screen);

	//Update the screen
	if( SDL_Flip( screen ) == -1 ) {
		return 1;
	}

	while(quit==false){

		while(SDL_PollEvent(&event)){

			if(event.type==SDL_QUIT){

				quit=true;
			}


		}
	}

	cleanUp();
	return 0;
}
