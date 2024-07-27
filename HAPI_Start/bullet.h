#pragma once
#include "entity.h"
#include<vector>
class bullet : public entity
{
private:
	// Vector2 m_dir;
	ESide m_side;
	int m_dir;
public:
	~bullet();
	bullet(std::string name) : entity(name) { m_alive = false; }
	void Update() override;
	//ESide GetSide() const override { return ESide::eSideNeutral; }
	void Intialize(int posX, int posY, ESide side); //TODO: set int to Vect2's

	ESide GetSide() const override { return ESide::eSideNeutral; } //temp fix due to need for an overide

	
};

