#include "stdafx.h"


int main(int argc, char **argv){

	Renderer *r = new Renderer();
	if( r->Init() )
		return -1;

	int buttonCoords[][3] = { 
		{268,229,105}, //NEW GAME x,y,w
		{253,254,135}, //RESTORE GAME
		{242,278,158}, //LOAD GAME
		{287,304, 69},  //CREDITS
		{274,329, 99}  //EXIT
	};
	const int BUTTON_HEIGHT = 14;

	//TODO: have a default graphic and any time a load fails, use that
	Texture *background = r->LoadTexture("../images/screens/titlepage.bmp");
	if( background == NULL )
		return 4;

	SDL_Event e;
	bool quit = false;

	while( !quit )
	{
		int m_startTicks = SDL_GetTicks();

		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			quit = true;
		//if (e.type == SDL_KEYDOWN)
			//quit = true;
		if (e.type == SDL_MOUSEBUTTONDOWN)
			quit = true;

		char *filepaths[] = { 
			"../images/screens/newgame.bmp",
			"../images/screens/restoregame.bmp",
			"../images/screens/loadgame.bmp",
			"../images/screens/credits.bmp",
			"../images/screens/exitgame.bmp"
		};

		//preload all the textures before displaying them

		Texture *textures[5];
		
		for (int count=0; count<sizeof(filepaths)/sizeof(filepaths[0]); count++)
			textures[count] = r->LoadTexture(filepaths[count]);

		// erase everything
		r->ClearFrame();
		background->Draw();

		// find if we are highlighting anything
		if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
		{
			for (int count=0; count<5; count++)
			{
				//Get mouse position
				int x, y;
				SDL_GetMouseState( &x, &y );

				// check to see if mouse is on this button
				if( x >= buttonCoords[count][0] 
				&&  x <  buttonCoords[count][0] + buttonCoords[count][2]
				&&  y >= buttonCoords[count][1]
				&&  y <  buttonCoords[count][1] + BUTTON_HEIGHT )
				{
					// create a texture and load the button
					textures[count]->Draw(buttonCoords[count][0],buttonCoords[count][1],buttonCoords[count][2],BUTTON_HEIGHT,0);
					break;
				}
			}
		}	

		r->DisplayFrame();

		// wait for the end of the frame
		while( (SDL_GetTicks() - m_startTicks) < 1000/30 )
			;
	}

	SDL_Quit();
	return 0;
}
