#include "entity.h"
#include"world.h"

constexpr int CheckRange{10}; //checks  with + - this number from pos (square around the point)

entity::~entity()
{

}

void entity::CheckCollision(entity& other)
{
	if (m_alive == true && other.m_alive == true)
	{
		for (int i = 0; i < CheckRange; i++)
		{
			for (int j = 0; j < CheckRange; j++)
			{
				if (m_posX + i == other.m_posX + i || m_posY + j == other.m_posY + j) //basic as only have position at (logic to check with an area of this ?)
				{
					m_Collided = true;
					HAPI.UserMessage("player -> Enemy Collision", "Error"); //currently this always activates :( TODO : Fix why this always activates as true :(
				}
			}
		}
	}
	
	for (int i = 0; i < CheckRange; i++)  //logic to check with an area i think :)
	{									// dont think this works, ares might be missed, but might work a bit 
		/*if (getm_posX() + CheckRange == other.getm_posX() + CheckRange)
			m_Collided = true;
		if (getm_posY() + CheckRange == other.getm_posY() + CheckRange)
			m_Collided = true;
		if (getm_posX() - CheckRange == other.getm_posX() - CheckRange)
			m_Collided = true;
		if (getm_posY() - CheckRange == other.getm_posY() - CheckRange)
			m_Collided = true;*/
	}
	if (m_Collided == false)
	{
		m_Collided = false;
	}
}

void entity::CheckScreenCollision(entity& other)
{

}

void entity::Fire(int bullposX, int bullposY)
{
	m_alive = true;
	m_posX = bullposX;
	m_posY = bullposY;
	//HAPI.UserMessage("FIRE !", "Error");
}