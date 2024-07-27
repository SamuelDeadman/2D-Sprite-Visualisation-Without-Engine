#include "Sprite.h"
#include <HAPI_lib.h>
#include <cassert>
#include "Rectangle.h"

bool Sprite::Create(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &m_data, m_width, m_height))
		return false;
	return true;
}

void Sprite::BlitFast(BYTE* screen, int screenWidth, int screenHeight, int sx, int sy)
{
	//void QuickBlit(BYTE * screen, int width, BYTE * textureData, int textureWidth, int textureHeight, int x, int y)
		{
			for (int newY = 0; newY < m_height; newY++)
			{
				int offset = (screenWidth * (sy + newY) + sx) * 4;
				int textureOffset = m_height * newY * 4;
				memcpy(screen + offset, m_data + textureOffset, m_width * 4); //issue in this part sos
			}
		}
}

void Sprite::BlitAlpha(BYTE* screen, int screenWidth, int screenHeight, int sx, int sy)
{
	//texture clipping of screen logic
	Rectangle screenRect(0, screenWidth, 0, screenHeight); // the screen info
	Rectangle textureRect(0, m_width, 0, m_height);  // the sprite info

	textureRect.Translate(sx, sy);
	textureRect.ClipTo(screenRect);
	textureRect.Translate(-sx, -sy);

	if (sx < 0)
		sx = 0;
	if (sy < 0)
		sy = 0;

//void AlphaBlit(BYTE * screen, int width, BYTE * textureData, int textureWidth, int textureHeight, int x, int y)

		BYTE* screenStart = screen + (sx + sy * screenWidth) * 4;
		BYTE* textureStart = m_data + (textureRect.left + textureRect.top * m_width) * 4;

		//BYTE* textureStart{ m_data }; //without clipping logic
		//int endOfLineIncrement{ screenWidth * 4 - m_width * 4 }; // slight change 
		
		int endOfLineIncrement = (screenWidth - textureRect.Width()) *4;
		int endOfLineScourceIncrement = (m_width - textureRect.Width()) *4;

		for (int y = 0; y < textureRect.Height(); y++)
		{
			for (int x = 0; x < textureRect.Width(); x++)
			{
				//assert(screen != nullptr);
				BYTE alpha = textureStart[3];
				if (alpha > 0)
				{
					BYTE blue = textureStart[0];
					BYTE green = textureStart[1];
					BYTE red = textureStart[2];
					if (alpha == 255)
					{
						memcpy(screenStart, textureStart, 4);
					}
					else
					{
						screenStart[0] = screenStart[0] + ((alpha * (blue - screenStart[0])) >> 8);
						screenStart[1] = screenStart[1] + ((alpha * (green - screenStart[1])) >> 8);
						screenStart[2] = screenStart[2] + ((alpha * (red - screenStart[2])) >> 8);
					}
				}
				//advance X
				screenStart += 4;
				textureStart += 4;
				
			}
			//advance Y 
			screenStart += endOfLineIncrement;
			textureStart += endOfLineScourceIncrement;
		}
}

Sprite::~Sprite()
{
	delete[]m_data;
}
