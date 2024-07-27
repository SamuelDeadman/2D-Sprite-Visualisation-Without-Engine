#pragma once
#include<string>
#include "entity.h"
class player : public entity //inheratance from entity
{
private:
	int m_lives{2};  //logic to reduce lives on no health, and loss when live = 0
public:
	~player();
	player(std::string name) : entity(name) {}
	void Update() override;  //overriding the base update which is empty
	void Intialize(int width, int height);
	ESide GetSide() const override { return ESide::eSidePlayer; }
};