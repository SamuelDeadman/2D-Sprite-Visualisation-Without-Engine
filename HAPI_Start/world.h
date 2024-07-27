#pragma once
#include "entity.h" //better to use a 'forwards declaration'
#include <vector>
#include "Visualisation.h"

//struct vec2 {
//	float x;
//	float y;
//};
//struct vec3 {
//	float x;
//	float y;
//	float speed;
//};

class world
{
private:
	std::vector<entity*> m_entityVector;
	std::vector<entity*> m_entityVectorBullets;
	std::vector<entity*> m_entityVectorPlayer;
	Visualisation *m_viz{nullptr}; //blackboxed
	size_t m_bulletStartIndex{0};
	//size_t m_bulletEndIndex{ 0 }; ??? idk why this 
public:
	~world();
	void Intialize(int width, int height);
	bool LoadLevel();
	void Update();
	void FireBullet(int posX,int posY); //TODO: change ints to Vector2's
	void SoundLoad(const std::string& filename);
	void SoundPlay(const std::string& filename);
};

