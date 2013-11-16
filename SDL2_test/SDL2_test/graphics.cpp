#include "stdafx.h"


Renderer::Renderer(): m_window(nullptr), m_renderer(nullptr), m_screenSurface(nullptr)
{
}

Renderer::~Renderer()
{
	if( m_renderer != nullptr )
		SDL_DestroyRenderer(m_renderer);

	if( m_window != nullptr )
		SDL_DestroyWindow(m_window);
}

int Renderer::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	m_window = SDL_CreateWindow("SDL2_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (m_window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		return 2;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		return 3;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  
	//SDL_RenderSetLogicalSize(m_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return 0;
}

void Renderer::ClearFrame()
{
	SDL_RenderClear(m_renderer);
}

void Renderer::DisplayFrame()
{
	SDL_RenderPresent(m_renderer);
}


Texture* Renderer::LoadTexture(const std::string &file)
{
	SDL_Texture *texture = IMG_LoadTexture(m_renderer, file.c_str());
		
	//Make sure converting went ok too
	if( texture != nullptr )
	{
		//Create our internal texture structure
		Texture *t = new Texture( texture, m_renderer );
		return t;
	}
	else
	{
		logSDLError(std::cout, "LoadTexture");
		return nullptr;
	}
}


Texture::Texture(SDL_Texture *t, SDL_Renderer *r)
{
	m_texture = t;
	m_renderer = r;
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_texture);
}


void Texture::Draw(int x, int y, int w, int h)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	if( w==-1 || h==-1)
	{
		//Query the texture to get its width and height to use
		SDL_QueryTexture(m_texture, NULL, NULL, &dst.w, &dst.h);
	}
	SDL_RenderCopy(m_renderer, m_texture, NULL, &dst);

}
