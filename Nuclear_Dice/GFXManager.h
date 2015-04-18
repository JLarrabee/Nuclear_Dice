#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
class GFXManager
{
public:
	GFXManager(void);
	~GFXManager(void);

	//-------------------Functions
	//Starts up SDL and creates window
	bool init();
	//Loads media
	bool loadMedia();
	//Frees media and shuts down SDL
	void close();
	// Load Surfaces and convert to screen parameters
	SDL_Surface* loadSurface( std::string path );

	//---------------------Variable Declarations
	//Main Window
	SDL_Window* gameWindow;

	//Main Surfaces
	SDL_Surface* gScreenSurface;
	SDL_Surface* currentSurface;

	//Window Dimensions
	int screenSizeX;
	int screenSizeY;

	//Images
	SDL_Surface* mainLogo;
	SDL_Surface* creditSplash;

};

