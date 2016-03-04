#include "PongApp.h"

bool PongApp::AppInit()
{
	if (m_Font.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 36, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
	{
		m_KeyPressed.CreateFromText(m_Window.GetRenderer(), "Key pressed: ", m_Font);
		m_MouseFocus.CreateFromText(m_Window.GetRenderer(), "Mouse Focus: ", m_Font);

		m_KeyFocus.CreateFromText(m_Window.GetRenderer(), "Key Focus: ", m_Font);
		m_Shown.CreateFromText(m_Window.GetRenderer(), "Shown: ", m_Font);
		m_Maximized.CreateFromText(m_Window.GetRenderer(), "Maximized: ", m_Font);

		m_Yes.CreateFromText(m_Window.GetRenderer(), "Yes", m_Font);
		m_No.CreateFromText(m_Window.GetRenderer(), "No", m_Font);
	}
	return true;
}


void PongApp::AppCleanup()
{
	m_Font.Release();
	m_KeyPressed.Release();
	m_MouseFocus.Release();
	m_Maximized.Release();
	m_KeyFocus.Release();
	m_Shown.Release();

	m_Yes.Release();
	m_No.Release();
}

void PongApp::AppRender(Renderer& renderer)
{
	int y = 0;
	m_KeyPressed.Render(renderer, 0, y);
	if (m_KeyDown == SDLK_UNKNOWN)
		m_No.Render(renderer, m_KeyPressed.GetWidth(), y);
	else
		m_Yes.Render(renderer, m_KeyPressed.GetWidth(), y);

	y += m_KeyPressed.GetHeight();

	m_MouseFocus.Render(renderer, 0, y);
	if (m_Window.hasMouseFocus())
		m_Yes.Render(renderer, m_MouseFocus.GetWidth(), y);
	else
		m_No.Render(renderer, m_MouseFocus.GetWidth(), y);

	y += m_MouseFocus.GetHeight();

	m_KeyFocus.Render(renderer, 0, y);
	if (m_Window.hasKeyboardFocus())
		m_Yes.Render(renderer, m_KeyFocus.GetWidth(), y);
	else
		m_No.Render(renderer, m_KeyFocus.GetWidth(), y);

	y += m_KeyFocus.GetHeight();

	m_Shown.Render(renderer, 0, y);
	if (m_Window.isShown())
		m_Yes.Render(renderer, m_Shown.GetWidth(), y);
	else
		m_No.Render(renderer, m_Shown.GetWidth(), y);

	y += m_Shown.GetHeight();

	m_Maximized.Render(renderer, 0, y);
	if (m_Window.isMaximized())
		m_Yes.Render(renderer, m_Maximized.GetWidth(), y);
	else
		m_No.Render(renderer, m_Maximized.GetWidth(), y);
}

bool PongApp::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
	m_KeyDown = key;

	return true;
}

bool PongApp::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
	if (m_KeyDown == key)
		m_KeyDown = SDLK_UNKNOWN;

	return true;
}

