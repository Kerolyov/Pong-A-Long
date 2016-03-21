#include "TextureManager.h"

#include <algorithm>

#include <sdl_assert.h>

#include "Renderer.h"
#include "Sprite.h"
#include "Texture.h"

TextureManager::~TextureManager()
{
	Release();
}

void TextureManager::Release()
{
	std::for_each(m_Textures.begin(), m_Textures.end(), [](std::shared_ptr<Texture>& pTexture) { if (pTexture) pTexture->Release(); });

	m_Textures.clear();
}

int TextureManager::AddTextureFromFile(Renderer& renderer, std::string filename)
{
	if (renderer.GetRenderPtr())
	{
		std::shared_ptr<Texture> pTexture(new Texture);

		if (pTexture)
		{
			pTexture->CreateFromFile(renderer, filename);

			return AddTexture(pTexture);
		}
		else
			return 0;
	}
	return 0;
}


int TextureManager::AddTexture(std::shared_ptr<Texture> pTexture)
{
	m_Textures.push_back(pTexture);

	return ++m_max_id;
}

void TextureManager::RenderTexture(Renderer& renderer, int ID, const SDL_Rect& dest_rect, const Sprite& sprite)
{
	if (ID < m_max_id)
	{
		std::shared_ptr<Texture> pTexture = m_Textures[ID];

		if (pTexture)
			pTexture->Render(renderer, dest_rect, sprite);
	}
}


