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
//	std::for_each(m_Textures.begin(), m_Textures.end(), [](std::unique_ptr<Texture>& pTexture) { if (pTexture) pTexture->Release(); });
	m_Textures.clear();

	m_max_id = 0;
}

std::unique_ptr<Texture>& TextureManager::GetTexture(int id)
{
	static std::unique_ptr<Texture> null_texture(new Texture);
	SDL_assert(null_texture);

	SDL_assert(m_max_id == m_Textures.size());
	SDL_assert(id >=0 && id < m_max_id);
	SDL_assert(m_Textures[id]);

	if (id >= 0 && id < m_max_id && m_Textures[id])
		return m_Textures[id];
	else
		return null_texture;
}

int TextureManager::AddTextureFromText(Renderer& renderer, std::string text, FontTTF& font)
{
	std::unique_ptr<Texture> pTexture(new Texture);

	SDL_assert(renderer.GetRenderPtr());
	SDL_assert(pTexture);
	if (pTexture && renderer.GetRenderPtr() && pTexture->CreateFromText(renderer, text, font))
		return AddTexture(std::move(pTexture));
	else
		return -1;
}

int TextureManager::AddTextureFromFile(Renderer& renderer, std::string filename)
{
	std::unique_ptr<Texture> pTexture(new Texture);

	SDL_assert(renderer.GetRenderPtr());
	SDL_assert(pTexture);
	if (pTexture && renderer.GetRenderPtr() && pTexture->CreateFromFile(renderer, filename))
		return AddTexture(std::move(pTexture));
	else
		return -1;
}


int TextureManager::AddTexture(std::unique_ptr<Texture> pTexture)
{
	m_Textures.push_back( std::move(pTexture) );
	SDL_assert(m_Textures.size() == m_max_id + 1);

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

