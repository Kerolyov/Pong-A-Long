#ifndef Texture_h__
#define Texture_h__
#pragma once

#include <string>
#include <SDL.h>

class Renderer;
class FontTTF;
class Sprite;

class Texture
{
public:
	Texture();
	~Texture();

	void Release();

	bool IsNull() { return (m_pTexture == nullptr); }

	void Render(Renderer& renderer, int x, int y, SDL_Rect*	pClipRect = nullptr);
	void RenderStretch(Renderer& renderer, SDL_Rect* pDestRect = nullptr, SDL_Rect*	pClipRect = nullptr);

	void Render(Renderer& renderer, const SDL_Rect& dest_rect, const Sprite& sprite);

	bool CreateFromFile(Renderer& renderer, std::string filename);

	bool CreateFromText(Renderer& renderer, std::string text, FontTTF& font);
	bool CreateFromText_Fast(Renderer& renderer, std::string text, FontTTF& font);

	bool CreateFromSurface(SDL_Surface* textSurface, Renderer &renderer);

	int GetHeight() { return m_Height;  }
	int GetWidth() { return m_Width;  }

private:
	SDL_Texture*  m_pTexture = nullptr;

	int m_Width = 0;
	int m_Height = 0;
};

#endif // Texture_h__

