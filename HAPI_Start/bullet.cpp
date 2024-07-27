#include "bullet.h"

bullet::~bullet()
{
	
}

void bullet::Update()
{
	if (m_alive == true)
	{
		m_posY = m_posY - 5; //sends bullet up !
		if (m_posY < 0)
		{
			m_alive = false;
			m_posY = -200;
			m_posX = -200; //sets bullet off screen when not in use (as its offscreen it is not draw so no slow down)
		}
		//check collision with screen !
	}
	//If off screen die !, if alive set alive false 
}

void bullet::Intialize(int posX, int posY, ESide side)
{ //manual bullet fire !
	m_alive = true;
	m_posY = posY;
	m_posX = posX;
}


