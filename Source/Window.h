#ifndef Window_h__
#define Window_h__
#pragma once

#include <string>
#include <SDL.h>
#include "Renderer.h"

class Window
{
public:
	Window();
	~Window();

	void Release();

	bool Create(std::string title, int x, int y, int w, int h, Uint32 flags);
	bool CreateRenderer();
	void ClearWindow();
	void Present();

	bool CanRender() { return (m_pWindow && m_Renderer.GetRenderPtr()); }

	Renderer& GetRenderer() { return m_Renderer;  }
	
private:
	SDL_Window* m_pWindow = nullptr;
	Renderer m_Renderer;

	int m_WindowID = 0;
	int m_Width = 0;
	int m_Height = 0;
};

#endif // Window_h__

