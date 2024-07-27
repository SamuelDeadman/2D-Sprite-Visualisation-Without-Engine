#pragma once
#include "entity.h"
class enemy : public entity
{
private:
	enum EnDirection
	{
		enEast,
		enWest
	};
	bool m_Active { false };
	int m_numOfEnemys { 0 };
	float m_speed { 1 };
	float m_speedvariation { 0 };
public:
	~enemy();
	enemy(std::string name) : entity(name) {}
	void Update() override;
	void Intialize(int width, int height);
	void slidemove();
	void CheckBottom();
	ESide GetSide() const override { return ESide::eSideEnemy; }
};

