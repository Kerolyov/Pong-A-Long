#include "TextureManager.h"

#include <algorithm>

#include <sdl_assert.h>

#include "Renderer.h"
#include "Texture.h"
#include "GameObject.h"
#include "Font_TTF.h"

TextureManager::~TextureManager()
{
	Release();
}

void TextureManager::Release()
{
	m_Textures.clear();

	m_max_id = 0;
}

std::unique_ptr<Texture>& TextureManager::GetTexture(int id)
{
	SDL_assert(id >=0 && id < m_max_id);
	SDL_assert(m_Textures[id]);

	return m_Textures[id];
}

int TextureManager::AddTextureFromText(Renderer& renderer, std::string text, FontTTF& font)
{
	SDL_assert(renderer.GetRenderPtr());
	std::unique_ptr<Texture> pTexture(new Texture);

	SDL_assert(pTexture);
	pTexture->CreateFromText(renderer, text, font);

	return AddTexture(std::move(pTexture));
}

int TextureManager::AddTextureFromFile(Renderer& renderer, std::string filename)
{
	SDL_assert(renderer.GetRenderPtr());
	std::unique_ptr<Texture> pTexture(new Texture);

	SDL_assert(pTexture);
	if (pTexture->CreateFromFile(renderer, filename))
		return AddTexture(std::move(pTexture));
	else
		return -1;
}


int TextureManager::AddTexture(std::unique_ptr<Texture> pTexture)
{
	m_Textures.push_back( std::move(pTexture) );

	return m_max_id++;
}


void TextureManager::RenderTexture(Renderer& renderer, const SDL_Rect& dest_rect, const Sprite& sprite)
{
	GetTexture( sprite.GetTextureID() )->Render(renderer, dest_rect, sprite);
}

void TextureManager::RenderTexture(Renderer& renderer, const GameObject& gameObject)
{
	RenderTexture(renderer, gameObject.GetSpriteRect(), gameObject.GetSprite());
}

void TextureManager::RenderTexture(Renderer& renderer, int id, int x, int y)
{
	GetTexture(id)->Render(renderer, x, y);
}

SDL_Rect TextureManager::GetTextureSize(int id)
{
	std::unique_ptr<Texture>& pTexture = GetTexture(id);

	return SDL_Rect{ 0, 0, pTexture->GetWidth(), pTexture->GetHeight() };
}

