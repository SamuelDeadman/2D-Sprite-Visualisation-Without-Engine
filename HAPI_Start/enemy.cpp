#include "enemy.h"
#include <HAPI_lib.h>
#include <ctime>
enemy::~enemy()
{
	
}

void enemy::Update()
{
	if (m_Active == true)
	{
		slidemove();
		CheckBottom();
	}
	if (m_alive == true || m_Active == false)
	{
		Intialize(rand() % 1024 + 1, 0);

		m_speedvariation = rand() % 2;
	}
}

void enemy::slidemove()
{
	m_speed = getm_speed();
	m_posY = m_posY + m_speed/2 + (m_speedvariation /4);
}

void enemy::CheckBottom()
{
	if (m_posY > 768) 
	{
		m_Active = false;
	}
}

void enemy::Intialize(int width, int height)
{
	m_Active = true;
	m_posX = width;
	m_posY = height;
}
