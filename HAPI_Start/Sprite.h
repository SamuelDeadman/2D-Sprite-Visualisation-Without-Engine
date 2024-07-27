#pragma once
#include <HAPI_lib.h>
using namespace HAPISPACE;

class Sprite
{
private:
	int m_width;
	int m_height;
	BYTE* m_data{ nullptr };
public:
	~Sprite();
	bool Create(const std::string& filename);
	
	void BlitFast(BYTE* screen, int screenWidth, int screenHeight, int sx, int sy);
	void BlitAlpha(BYTE* screen, int screenWidth, int screenHeight, int sx, int sy);
};

