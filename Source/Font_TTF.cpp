#include "Font_TTF.h"

#include <SDL_ttf.h>
#include <exception>


FontTTF::FontTTF(const char* file, int ptsize, SDL_Color textColor)
{
	if (file && ptsize)
	{
		if (!LoadFont(file, ptsize, textColor))
			throw std::exception("Font load failed in FontTTF constructor");
	}
}

FontTTF::~FontTTF()
{
	Release();
}

bool FontTTF::LoadFont(const char* file, int ptsize, SDL_Color textColor)
{
	m_pFont = TTF_OpenFont(file, ptsize);

	if (m_pFont == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Font not loaded", nullptr);
		m_ptsize = 0;
		return false;
	}

	m_ptsize = ptsize;
	m_textColour = textColor;
	return true;
}

void FontTTF::Release()
{
	TTF_CloseFont(m_pFont);
	m_pFont = nullptr;
	m_ptsize = 0;
}



