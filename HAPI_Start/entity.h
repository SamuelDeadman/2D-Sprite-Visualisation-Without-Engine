#pragma once
#include <string>


enum ESide
{
	eSideNeutral,
	eSideEnemy,
	eSidePlayer
};

class entity
{
private:
	bool m_Collided{ false };
	int m_health{ 1 };
	int m_speed{ 1 };
public:
	
	~entity();
	std::string m_spriteName; //TODO : private this logic !
	entity(std::string name) : m_spriteName(name) {}
	virtual void Update()=0;
	bool m_alive{ false };
	float m_posX, m_posY;
	int getm_posX() {
		return int(m_posX);
	};
	int getm_posY() {
		return int(m_posY);
	};
	int getm_speed() {
		return m_speed;
	};
	void CheckCollision(entity& other);
	void CheckScreenCollision(entity& other);
	void Fire(int bullposX, int bullposY);
	virtual ESide GetSide() const = 0; //hard coded side
};