#include "Window.h"



Window::Window()
{

}

Window::~Window()
{
	Release();
}

void Window::Release()
{
	m_Renderer.Release();

	// Destroy the window
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
}

bool Window::Create(std::string title, int x, int y, int w, int h, Uint32 flags)
{
	Release();

	m_pWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);

	if (m_pWindow == nullptr)
		return false;

	m_Width = w;
	m_Height = h;

	//Grab window identifier 
	m_WindowID = SDL_GetWindowID(m_pWindow);

	return true;
}

bool Window::CreateRenderer()
{
	return m_Renderer.Create(m_pWindow);
}

void Window::ClearWindow()
{
	m_Renderer.ClearBackBuffer();
}

void Window::Present()
{
	if (m_pWindow)
		m_Renderer.Present();
}
