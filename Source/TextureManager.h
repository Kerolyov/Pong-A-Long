#ifndef TextureManager_h__
#define TextureManager_h__
#pragma once

#include <vector>
#include <memory>

#include <SDL.h>

class Texture;
class Sprite;
class Renderer;

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager();

	void Release();

	int AddTextureFromFile(Renderer& renderer, std::string filename);
	int AddTexture(std::shared_ptr<Texture> pTexture);

	void RenderTexture(Renderer& renderer, int ID, const SDL_Rect& dest_rect, const Sprite& sprite);

protected:
	
private:
	std::vector<std::shared_ptr<Texture>> m_Textures;
	int m_max_id = 0;
};

#endif // TextureManager_h__

