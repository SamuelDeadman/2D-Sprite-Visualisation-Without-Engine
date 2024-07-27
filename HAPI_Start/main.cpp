/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there is a batch file for creating a redistributable Demo folder

	For help using HAPI please see the Reference folder in the HAPI sub-directory
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include<time.h> 
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

#include "Visualisation.h"
#include "Rectangle.h"
#include <cassert>
#include "world.h"
#include "entity.h"
#include "player.h"



// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

//void ClearOne(BYTE* screen, int width, int height, float X, float Y, float Z, HAPI_TColour colour);
//void QuickBlit(BYTE* screen, int width, BYTE* textureData, int textureWidth, int textureHeight, int x, int y);
//void AlphaBlit(BYTE* screen, int width, BYTE* textureData, int textureWidth, int textureHeight, int x, int y);
constexpr int KNumStars = 0; // number of stars  //STARS PART

struct Star {
	float x;
	float z;
	float y;
};

int width{ 1024 };
int height{ 768 };
int depth{ 100 };

void HAPI_Main()
{
	world* aWorld = new world();
	aWorld->Intialize(width, height); // graphics linked
	aWorld->LoadLevel(); // start !

	if (!HAPI.Initialise(width, height, "Sam's HAPI MS1"))
		return;
	
	DWORD lastTimeUpdated = HAPI.GetTime();
	const DWORD kTickTime = 1000 / 20;

	HAPI.SetShowFPS(true);
	
	HAPI_TColour colour(HAPI_TColour::WHITE); //used preset RGB Vals

	int x = 100;// might be legacy atm  ?
	int y = 200;// might be legacy atm  ?
	bool LoadedStatic{ false }; 

	while (HAPI.Update())
	{
		BYTE* screen = HAPI.GetScreenPointer();
		assert(screen != 0);

		//memset(screen, 0, width * height * 4); //SCREEN RESET allowing for movemnt / removing old stuff
		//viz->ClearToColour(HAPI_TColour::BLACK);

		aWorld->Update();

		DWORD timeSinceLastUpdate = HAPI.GetTime() - lastTimeUpdated;
		if (timeSinceLastUpdate >= kTickTime)
		{
			//aWorld->Update();
			//position = position + speed * dir scrrenPos = oldPos + (newPos - oldPos) * dt; 

			//update system logic
			lastTimeUpdated = HAPI.GetTime();
		}
		float dt = (float)timeSinceLastUpdate / kTickTime; //pass dt into render function

		//HAPI.RenderText(100, 200, HAPI_TColour::CYAN, "Hello", 60);
		//memset(screen, 150, width * height * 4);  //not an actual error - fix - (int)width
	}
	delete aWorld;
}



//void ClearOne(BYTE* screen, int width, int height, float X, float Y, float Z, HAPI_TColour colour)
//{
//	constexpr int eyeDist{ 100 };
//	int halfW = width / 2;
//	int halfH = height / 2;
//	float Sx = ((eyeDist * (X - halfW)) / (Z + eyeDist)) + halfW;
//	float Sy = ((eyeDist * (Y- halfH)) / (Z + eyeDist)) + halfH;
//	int offset = (width * int(Sy) + int(Sx)) * 4;
//	memcpy(screen + offset, &colour, 4);
//}