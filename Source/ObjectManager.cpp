#include "ObjectManager.h"

#include <sdl_assert.h>

#include <algorithm>

#include "TextureManager.h"
#include "Texture.h"
#include "Renderer.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	Release();
}

void GameObjectManager::Release()
{
	m_Objects.clear();

	m_max_id = 0;
}

std::unique_ptr<GameObject>& GameObjectManager::GetObject(int id)
{
	SDL_assert(id >= 0 && id < m_max_id);
	SDL_assert(m_Objects[id]);

	return m_Objects[id];
}

int GameObjectManager::AddObject(std::unique_ptr<GameObject>& pObject)
{
	m_Objects.push_back(std::move(pObject));

	return m_max_id++;
}

void GameObjectManager::RenderObjects(TextureManager& texture_manager, Renderer& renderer)
{
	std::for_each(m_Objects.begin(), m_Objects.end(), [&](std::unique_ptr<GameObject>& pObject) { if (pObject.get()) texture_manager.RenderTexture(renderer, *pObject); } );
}

void GameObjectManager::UpdateObjects(double dt)
{
	std::for_each(m_Objects.begin(), m_Objects.end(), [&](std::unique_ptr<GameObject>& pObject) { if (pObject.get()) pObject->Update(dt); });
}
