#include "PongApp.h"

bool PongApp::AppInit()
{
	if (m_Font.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 36, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
	{
		bool success = m_textTexture.CreateFromText(m_Window.GetRenderer(), "Quality render text", m_Font);
		success = success & m_textTexture_fast.CreateFromText_Fast(m_Window.GetRenderer(), "Fast render text", m_Font);

		if (success)
			return true;
	}

	return false;
}

void PongApp::AppCleanup()
{
	m_Font.Release();
	m_textTexture.Release();
	m_textTexture_fast.Release();
}


void PongApp::AppRender(Renderer& renderer)
{
	m_textTexture.Render(renderer, 0, 0);
	m_textTexture_fast.Render(renderer, 0, m_textTexture.GetHeight());
}

