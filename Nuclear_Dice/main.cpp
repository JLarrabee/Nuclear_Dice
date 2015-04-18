// Nuclear Dice
// Concept Credit/Co Main Developer - Jason Larrabee
// Co Main Developer - Bryan Jump

#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"
#include <string>

#include "GFXManager.h"

//Keyboard event
SDL_Event e;

//Main Loop Control
bool quit = false;

//-----------------------Structures




int main( int argc, char* args[] )
{
	//Load up our Graphics Manager
	GFXManager* gfx = new GFXManager();
    //Start up SDL and create window
    if( !gfx->init() )
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Not Initialized", "Could Not Initialize!", NULL);
    }
    else
    {
    //Load media
        if( !gfx->loadMedia() )
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Media Not loaded", "Could Not Load Media File!", NULL);
        }
        else
        {
			while(!quit)
			{
				//Handle events on queue ---------------Event Queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
					else if( e.type == SDL_KEYUP)		// used for events that need to be fired once per keystroke
					{
						switch( e.key.keysym.sym )
						{
						case SDLK_RETURN:
							gfx->currentSurface = gfx->creditSplash;
							break;
						case SDLK_HOME:
							gfx->currentSurface = gfx->mainLogo;
							break;
						}

					}
					else if( e.type == SDL_KEYDOWN)		// constant event if key is down
					{

					}
                }

				if(!quit)
				{
					//Apply the image
					SDL_BlitScaled( gfx->currentSurface, NULL, gfx->gScreenSurface, NULL );
				}
				else
				{
					SDL_BlitSurface(gfx->currentSurface, NULL, gfx->gScreenSurface, NULL );
					//Pause
				}


				//Update the surface
				SDL_UpdateWindowSurface( gfx->gameWindow );
				if(quit)
				{
				}
			}

		}
	}

	//Free resources and close SDL
    gfx->close();

    return 0;

}

