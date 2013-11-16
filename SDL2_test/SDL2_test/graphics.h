#ifndef __GRAPHICS__
#define __GRAPHICS__

const int SCREEN_WIDTH	= 640;
const int SCREEN_HEIGHT	= 480;
const int SCREEN_BPP = 32;

extern SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

class Texture;

class Renderer
{
public:
	Renderer();
	~Renderer();

	int Init();
	void ClearFrame();
	void DisplayFrame();
	Texture* LoadTexture(const std::string &file);

protected:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Surface *m_screenSurface;
};


class Texture
{
public:
	Texture( SDL_Texture *t, SDL_Renderer *r);
	~Texture();

	void Draw( int x=0, int y=0, int w=-1, int h=-1 );

protected:
	SDL_Texture *m_texture;
	SDL_Renderer *m_renderer;
};

#endif
