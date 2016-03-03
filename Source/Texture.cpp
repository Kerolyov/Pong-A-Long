#include "Texture.h"

#include <SDL_image.h>
#include "SDLErrorReport.h"
#include "Renderer.h"


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

void Texture::Render(Renderer& renderer)
{
	if (renderer.GetRenderPtr() && m_pTexture)
		SDL_RenderCopy(renderer.GetRenderPtr(), m_pTexture, nullptr, nullptr);
}

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
		Release();
		m_pTexture = SDL_CreateTextureFromSurface(renderer.GetRenderPtr(), pSurface);

		if (m_pTexture != nullptr)
		{
			// Success!  So save the Texture dimensions in pixels then clear the surface used for loading
			m_Width = pSurface->w;
			m_Height = pSurface->h;

			SDL_FreeSurface(pSurface);
		}
		else
		{
			// Failure! Clear surface and report error
			SDL_FreeSurface(pSurface);

			Error2MsgBox("Could not create texture loaded from file.\n");
			return false;
		}
	}
	return true;
}
