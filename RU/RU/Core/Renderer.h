#pragma once
#include <SDL.h>
#include <SDL_image.h>
class Renderer
{
public:
	static Renderer* Get() { return instance = (instance != nullptr) ? instance : instance = new Renderer(); }
	
	void ClearScreen();
	void Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
	void Display();
	SDL_Texture* LoadTexture(const char* filepath);
	inline SDL_Window* GetWindow() { return window; }
	inline SDL_Renderer* GetRenderer() { return renderer; }
	

	~Renderer();
protected:
	Renderer();

private:
	static Renderer* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

