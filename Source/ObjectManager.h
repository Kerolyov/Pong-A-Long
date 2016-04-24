#ifndef ObjectManager_h__
#define ObjectManager_h__
#pragma once

#include <vector>
#include <memory>

#include "GameObject.h"

class TextureManager;
class Renderer;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Release();

	std::unique_ptr<GameObject>& GetObject(int id);
	int AddObject(std::unique_ptr<GameObject>& pObject);

	void RenderObjects(TextureManager& texture_manager, Renderer& renderer);
	void UpdateObjects(double dt);
	
private:
	std::vector<std::unique_ptr<GameObject>> m_Objects;
	int m_max_id = 0;
};

#endif // ObjectManager_h__

