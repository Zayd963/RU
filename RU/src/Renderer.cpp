#include "Renderer.h"
#include <iostream>

Renderer* Renderer::instance = nullptr;

Renderer::Renderer()
{
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}



void Renderer::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void Renderer::Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst)
{
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Renderer::Display()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* Renderer::LoadTexture(const char* filepath)
{
	SDL_Texture* temp = nullptr;
	temp = IMG_LoadTexture(renderer, filepath);

	if (temp == nullptr)
		std::cout << "Failed to load texture error: " << IMG_GetError() << std::endl;

	return temp;
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete instance;
}


