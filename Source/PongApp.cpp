#include "PongApp.h"

bool PongApp::AppInit()
{
	Renderer& renderer = m_Window.GetRenderer();

	if (!m_Ball.CreateFromFile(renderer, "..\\gfx\\ball.png"))
		return false;

	if (m_Font.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 16, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
	{
		bool success = m_textInstruct.CreateFromText(renderer, "Press space to reset ball", m_Font);

		return success;
	}
	return false;
}


void PongApp::AppCleanup()
{
	m_Font.Release();

	m_Ball.Release();
	m_textInstruct.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	int y = 0;
	m_textInstruct.Render(renderer, 0, 0);
	m_Ball.Render(renderer, m_Window.GetWidth() / 2, m_Window.GetHeight() / 2);
}

bool PongApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
//	m_KeyDown = key;

	return true;
}

bool PongApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
// 	if (m_KeyDown == key)
// 		m_KeyDown = SDLK_UNKNOWN;

	return true;
}

