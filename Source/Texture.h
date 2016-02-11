#ifndef Texture_h__
#define Texture_h__
#pragma once

#include <string>
#include <SDL.h>

class Renderer;

class Texture
{
public:
	Texture();
	~Texture();

	void Release();

	void Render(Renderer& renderer);

	bool CreateFromFile(Renderer& renderer, std::string filename);

private:
	SDL_Texture*  m_pTexture = nullptr;
	int m_Width = 0;
	int m_Height = 0;
};

#endif // Texture_h__

