#include "GFXManager.h"


GFXManager::GFXManager(void)
{
	gameWindow = NULL;
	gScreenSurface = NULL;
	currentSurface = NULL;

	screenSizeX = 640;
	screenSizeY = 480;

	mainLogo = NULL;
	creditSplash = NULL;
}


GFXManager::~GFXManager(void)
{
}

bool GFXManager::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Not Initialized", "Could Not Initialize!", NULL);
        success = false;
    }
    else
    {
        //Create window
		gameWindow = SDL_CreateWindow( "Nuclear Dice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenSizeX, screenSizeY, SDL_WINDOW_SHOWN );
        if( gameWindow == NULL )
        {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window Not Created!", "The window could not be created!", NULL);
            success = false;
        }
        else
        {
			// Initialize Ability to Load PNG
			int imgFlags = IMG_INIT_PNG;
			if ( !( IMG_Init( imgFlags ) & imgFlags ))
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Not Initialized", IMG_GetError(), NULL);
				success = false;
			}
			else
			{
				 //Get window surface
				 gScreenSurface = SDL_GetWindowSurface( gameWindow );
			}
        }
    }
	return success;
}

bool GFXManager::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    mainLogo = loadSurface( "NuclearDice_MainLogo.png" );
    if( mainLogo == NULL )
    {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Image Not Loaded!", "The image file could not be found!", NULL);
        success = false;
    }
	// load secondary quit image
	creditSplash = loadSurface("CreditSplash.png");
	if( creditSplash == NULL )
    {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Quit Image Not Loaded!", "The image file could not be found!", NULL);
        success = false;
    }
	currentSurface = mainLogo;
    return success;
}

void GFXManager::close()
{
    //Deallocate surface
    SDL_FreeSurface( mainLogo );
	SDL_FreeSurface( creditSplash );
    mainLogo = NULL;
	creditSplash = NULL;

    //Destroy window
    SDL_DestroyWindow( gameWindow );
    gameWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* GFXManager::loadSurface( std::string path )
{
	//Image to Return
	SDL_Surface* finalSurface = NULL;

	//Load Image
	SDL_Surface* tempSurface = IMG_Load( path.c_str() );
	if( tempSurface == NULL )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Not Initialized", IMG_GetError(), NULL);
	}
	else
	{
		//Convert surface to screen format
		finalSurface = SDL_ConvertSurface( tempSurface, gScreenSurface->format, NULL );
		if( finalSurface == NULL )
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Not Initialized", SDL_GetError(), NULL);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( tempSurface );
	}

	return finalSurface;
}