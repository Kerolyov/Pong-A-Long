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
		Error2MsgBox("Could not load texture from file.\n");
		return false;
	}
	else
	{
		Release();
		m_pTexture = SDL_CreateTextureFromSurface(renderer.GetRenderPtr(), pSurface);
		SDL_FreeSurface(pSurface);

		if (m_pTexture != nullptr)
		{
			m_Width = pSurface->w;
			m_Height = pSurface->h;
		}
		else
		{
			Error2MsgBox("Could not create texture loaded from file.\n");
			return false;
		}
	}
	return true;
}
