#include "world.h"
#include"player.h"
#include "Visualisation.h"
#include"enemy.h"
#include"bullet.h"

world::~world()
{
	delete m_viz;
	for (auto* p : m_entityVector)
	{
		delete p;
	}
	delete m_viz;
	for (auto* pp : m_entityVectorBullets)
	{
		delete pp;
	}
	delete m_viz;
	for (auto* ppp : m_entityVectorPlayer)
	{
		delete ppp;
	}
}
void world::Intialize(int width, int height)
{
	m_viz = new Visualisation();
	m_viz->Intialise(width, height);
}

constexpr int KNumBullets = 100; //max about of bullets on screen at one time
constexpr int KNumEnemys = 10; //max about of enemys on screen at one time

bool bulladded = { false };

bool world::LoadLevel()
{
	SoundLoad("Data\\gun2.wav");
	//sound file sourced form https://www.soundjay.com/gun-sound-effect.html
	//"You are allowed to use the sounds on our website free of charge and royalty free in your projects"

	//bullets 
	if (!m_viz->LoadSprite("Data\\alphaThing.tga", "Bullet"))
	{
		HAPI.UserMessage("background File failed to loaded in world", "Error");
		return false;
	}

	m_bulletStartIndex = m_entityVector.size();
	
	for (int i = 0; i < KNumBullets; i++)
	{
		bullet* newBullet = new bullet("Bullet");
		m_entityVector.push_back(newBullet);//adds to entity vector 
		m_entityVectorBullets.push_back(newBullet);//list only for bullets
	}//bullets end
	
	//sprites
	if (!m_viz->LoadSprite("Data\\background.tga", "Background"))
	{
		HAPI.UserMessage("background File failed to loaded in world", "Error");
		return false;
	}
	if (!m_viz->LoadSprite("Data\\playerSprite.tga", "Player"))
	{
		HAPI.UserMessage("playerSprite File failed to loaded in world", "Error");
		return false;
	}
	if (!m_viz->LoadSprite("Data\\playerSprite.tga", "Enemy"))
	{
		HAPI.UserMessage("playerSprite File failed to loaded in world", "Error");
		return false;
	}

	//ASSUMPTION only one player !
	player* aPlayer = new player("Player"); //child class pointer
	m_entityVector.push_back(aPlayer); //adds to entity vector 
	m_entityVectorPlayer.push_back(aPlayer); //adds to  player entity vector 
	//initalised with possition, pass grapgics to use

	for (int i = 0; i < KNumEnemys; i++)
	{
		enemy* aEnemy = new enemy("Enemy");
		m_entityVector.push_back(aEnemy);
	}//sprites end
	
	return false;
	
}

void world::Update()
{
	BYTE* screen = HAPI.GetScreenPointer();//gets the current pointer for the screen  of 'screen'
	//call clear screen once per update
	m_viz->ClearToColour(screen, HAPI_TColour::BLACK); // screen reset from last draw / update

	for (auto* p : m_entityVector) //all enemys, player, bullets auto added and updated thought this :)
	{
		p->Update();//all entities have an updates, depending on the game states changes what each entity does TODO : Implement state system, ie Startup, Live, Reset, Endscreen 
	}

	for (size_t entitya1 = 0; entitya1 < m_entityVector.size(); entitya1++) // draws all the sprites in the main entity list
	{
		m_viz->DrawSprite(m_entityVector[entitya1]->m_spriteName, screen, m_entityVector[entitya1]->m_posX, m_entityVector[entitya1]->m_posY);
	}

	//for (size_t entity1 = 0; entity1 < m_entityVector.size(); entity1++) //collission compares list of main entity list, to the one next to it (TODO : changes so only check alive entities)
	//{
	//	for (size_t entity2 = 0; entity2 < m_entityVector.size(); entity2++) //collission compares list of all entities 
	//	{
	//	//m_entityVector[entity1]->CheckCollision(*m_entityVector[entity1 + 1]);
	//	}
	//}
	const HAPI_TKeyboardData& keyData1{ HAPI.GetKeyboardData() };
	//fire bullet from character (following one player character assumption but allows expansion of mutiple characters with limited changes)
	if (keyData1.scanCode['R'])
	{
		for (int i = 0; i < m_entityVectorPlayer.size(); i++)
		{
			FireBullet(m_entityVectorPlayer[i]->m_posX, m_entityVectorPlayer[i]->m_posY);
		}
	}
}

void world::FireBullet(int posX, int posY)
{
	for (int i = 0; i < m_entityVectorBullets.size(); i++)
	{
		if (m_entityVectorBullets[i]->m_alive==false && bulladded==false)
		{
			m_entityVectorBullets[i]->Fire(posX, posY);
			//HAPI.UserMessage("FIRE !", "Error");
			bulladded = true;
			SoundPlay("Data\\gun2.wav"); 
			//sound file sourced form https://www.soundjay.com/gun-sound-effect.html
			//"You are allowed to use the sounds on our website free of charge and royalty free in your projects"
		}
		
	}
	bulladded = false;
}
//sound logic
void world::SoundLoad(const std::string& filename)
{
	HAPI.LoadSound(filename);
}

void world::SoundPlay(const std::string& filename)
{
	int soundInstanceID;
	const HAPI_TSoundOptions options(0.02f, true, 0); //sounds settings allowing for sound to not deafen the user - WARNING logic might be needed as to not allow extreme soudsn to be played as that could be possible 
	HAPI.PlaySound(filename, options, soundInstanceID);//could have setting specificed aloowing for customisation

	//HAPI.PlaySound(filename);
	//HAPI.UserMessage("SoundPlay !", "Test");
}
