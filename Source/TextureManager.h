#ifndef TextureManager_h__
#define TextureManager_h__
#pragma once

#include <vector>
#include <memory>

#include <SDL.h>

class Texture;
class Sprite;
class Renderer;
class GameObject;
class FontTTF;

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager();

	void Release();

	std::unique_ptr<Texture>& GetTexture(int id);

	int AddTextureFromText(Renderer& renderer, std::string text, FontTTF& font);
	int AddTextureFromFile(Renderer& renderer, std::string filename);
	int AddTexture(std::unique_ptr<Texture> pTexture);

	void RenderTexture(Renderer& renderer, int id, int x, int y);
	void RenderTexture(Renderer& renderer, const SDL_Rect& dest_rect, const Sprite& sprite);
	void RenderTexture(Renderer& renderer, const GameObject& gameObject);

	SDL_Rect GetTextureSize(int id);

protected:
	
private:
	std::vector<std::unique_ptr<Texture>> m_Textures;
	int m_max_id = 0;
};

#endif // TextureManager_h__

