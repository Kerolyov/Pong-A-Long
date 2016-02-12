#ifndef Texture_h__
#define Texture_h__
#pragma once

#include <string>
#include <SDL.h>

class Renderer;
class FontTTF;

class Texture
{
public:
	Texture();
	~Texture();

	void Release();

	void Render(Renderer& renderer, int x, int y);
	void RenderStretch(Renderer& renderer, SDL_Rect* pDestRect = nullptr);

	void SetClipRect(SDL_Rect* rect) { m_pClipRect = rect; }

	bool CreateFromFile(Renderer& renderer, std::string filename);

	bool CreateFromText(Renderer& renderer, std::string text, FontTTF& font);
	bool CreateFromText_Fast(Renderer& renderer, std::string text, FontTTF& font);

	bool CreateFromSurface(SDL_Surface* textSurface, Renderer &renderer);

	int GetHeight() { return m_Height;  }
	int GetWidth() { return m_Width;  }

private:
	SDL_Texture*  m_pTexture = nullptr;
	SDL_Rect*	m_pClipRect = nullptr;
	int m_Width = 0;
	int m_Height = 0;
};

#endif // Texture_h__

