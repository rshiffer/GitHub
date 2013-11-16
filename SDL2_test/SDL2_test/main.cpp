#include "stdafx.h"


int main(int argc, char **argv){

	Renderer *r = new Renderer();
	if( r->Init() )
		return -1;

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
		if (e.type == SDL_KEYDOWN)
			quit = true;
		if (e.type == SDL_MOUSEBUTTONDOWN)
			quit = true;

		r->ClearFrame();
		background->Draw();
		r->DisplayFrame();

		// wait for the end of the frame
		while( (SDL_GetTicks() - m_startTicks) < 1000/30 )
			;
	}

	SDL_Quit();
	return 0;
}
