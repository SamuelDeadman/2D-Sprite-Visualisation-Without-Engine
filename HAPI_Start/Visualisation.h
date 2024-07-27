#pragma once
#include <HAPI_lib.h>
#include <unordered_map>;

class Sprite;

using namespace HAPISPACE;
class Visualisation
{
private:
	int m_screenWidth;
	int m_screenHeight;
	BYTE* m_screen{ nullptr };
	std::unordered_map<std::string, Sprite*> m_spriteMap;

public:
	~Visualisation();
	bool Intialise(int sw, int sh); //start width start height
	void ClearToColour(BYTE* screen, HAPI_TColour col);
	
	bool LoadSprite(const std::string& filename, const std::string& name);
	void DrawSprite(const std::string& name, BYTE* screen, int sx, int sy);
};

