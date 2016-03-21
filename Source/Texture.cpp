#include "Texture.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDLErrorReport.h"
#include "Renderer.h"
#include "Font_TTF.h"
#include "GameObject.h"

Texture::Texture()
{

}

Texture::~Texture()
{
	Release();
}

void Texture::Release()
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = nullptr;
	m_Width = 0;
	m_Height = 0;
}

// -----------------------------------------------------------------------------------------

void Texture::Render(Renderer& renderer, int x, int y, SDL_Rect* pClipRect /*= nullptr*/)
{
	SDL_Rect image_rect;

	if (pClipRect)
		image_rect = { x, y, pClipRect->w, pClipRect->h };
	else
		image_rect = { x, y, m_Width, m_Height };
	RenderStretch(renderer, &image_rect, pClipRect);
}

void Texture::RenderStretch(Renderer& renderer, SDL_Rect* pDestRect /*= nullptr*/, SDL_Rect* pClipRect /*= nullptr*/)
{
	if (renderer.GetRenderPtr() && m_pTexture)
		SDL_RenderCopyEx(renderer.GetRenderPtr(), m_pTexture, pClipRect, pDestRect, 0.0, nullptr, SDL_FLIP_NONE);
}

void Texture::Render(Renderer& renderer, const SDL_Rect& dest_rect, const Sprite& sprite)
{
	if (renderer.GetRenderPtr() && m_pTexture)
	{
		SDL_RenderCopyEx(renderer.GetRenderPtr(), m_pTexture, 
						&sprite.m_ClipRect, &dest_rect,
						sprite.m_rotation_angle, &sprite.m_RotationCentre,
						sprite.m_Flip);
	}
}

// -----------------------------------------------------------------------------------------

bool Texture::CreateFromFile(Renderer& renderer, std::string filename)
{
	SDL_Surface* pSurface = IMG_Load(filename.c_str());

	if (!pSurface)
	{
		// Failed to load from file
		Error2MsgBox("Could not load texture from file.\n");
		return false;
	}
	else
	{
		// Loaded ok, so convert to texture
		return CreateFromSurface(pSurface, renderer);
	}

	return true;
}

bool Texture::CreateFromText(Renderer& renderer, std::string text, FontTTF& font)
{
	if (!font.GetFontPtr())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Font not loaded", nullptr);
		return false;
	}

	SDL_Surface* textSurface = TTF_RenderText_Blended(font.GetFontPtr(), text.c_str(), font.GetColor() );

	return CreateFromSurface(textSurface, renderer);
}

bool Texture::CreateFromText_Fast(Renderer& renderer, std::string text, FontTTF& font)
{
	if (!font.GetFontPtr())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Font not loaded", nullptr);
		return false;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid( font.GetFontPtr(), text.c_str(), font.GetColor() );

	return CreateFromSurface(textSurface, renderer);
}

bool Texture::CreateFromSurface(SDL_Surface* textSurface, Renderer &renderer)
{
	Release();

	if (textSurface == nullptr)
	{
		Error2MsgBox("Tried to create texture from invalid surface.\n");
		return false;
	}

	//Create texture from surface pixels 
	m_pTexture = SDL_CreateTextureFromSurface(renderer.GetRenderPtr(), textSurface);
	if (m_pTexture == nullptr)
		Error2MsgBox("Unable to create texture from surface!\n");
	else
	{
		//Get image dimensions 
		m_Width = textSurface->w;
		m_Height = textSurface->h;
	}
	//Get rid of old surface 
	SDL_FreeSurface(textSurface);

	return m_pTexture != nullptr;
}
