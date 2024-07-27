#include "player.h"
#include"Visualisation.h"
#include <cassert>

player::~player()
{ 
}

void player::Update()
{
	if (m_alive == true)
	{
		const HAPI_TKeyboardData& keyData{ HAPI.GetKeyboardData() }; //does this neeed to be called every time ?

		if (keyData.scanCode['W'])
			m_posY = m_posY - getm_speed();
		if (keyData.scanCode['S'])
			m_posY = m_posY + getm_speed();
		if (keyData.scanCode['A'])
			m_posX = m_posX - getm_speed();
		if (keyData.scanCode['D'])
			m_posX = m_posX + getm_speed();
		if (keyData.scanCode['Q'])
		{
			m_posY = m_posY - getm_speed();
			m_posX = m_posX - getm_speed();
		}
		if (keyData.scanCode['E'])
		{
			m_posY = m_posY - getm_speed();
			m_posX = m_posX + getm_speed();
		}
		
	}
	if (m_alive == false && m_lives > 0)
	{
		Intialize(512, 700);
	}
	if (m_lives <= 1) 
	{
		m_alive = false;
	}
}

void player::Intialize(int width, int height)
{
	m_alive = true;
	m_posX = width;
	m_posY = height;
}