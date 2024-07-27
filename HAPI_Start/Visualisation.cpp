#include "Visualisation.h"
#include "Sprite.h"

bool Visualisation::Intialise(int sw, int sh)
{
	m_screenWidth = sw;
	m_screenHeight = sh;
	return true;
}

void Visualisation::ClearToColour(BYTE* screen, HAPI_TColour col)
{
	//BYTE* temp{ screen };
		for (int i = 0; i < m_screenWidth * m_screenHeight; i++)
		{
			memcpy(screen, &col, 4);
			screen += 4;
		}
}

bool Visualisation::LoadSprite(const std::string& filename, const std::string& name)
{
	Sprite* newSprite = new Sprite;
	if (!newSprite->Create(filename))
	{
		delete newSprite;
		return false;
	}
	m_spriteMap[name] = newSprite;
	return true;
}

void Visualisation::DrawSprite(const std::string& name, BYTE* screen, int sx, int sy)
{
	m_spriteMap[name]->BlitAlpha(screen, m_screenWidth, m_screenHeight, sx, sy);
}

Visualisation::~Visualisation()
{
	//delete[]m_screen;
	for (auto p : m_spriteMap)
	{
		delete(p.second);
	}
}
