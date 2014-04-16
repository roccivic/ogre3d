#ifndef __Floor_h_
#define __Floor_h_
#include "BaseApplication.h"
#include "Player.h"

class Floor
{
public:
    Floor(Ogre::SceneManager* mSceneMgr, Player* player);
    ~Floor();
	void makeFloor();
	void tick(const Ogre::FrameEvent& evt);
	bool** getSpotlights();

private:
	Player* player;
	Ogre::SceneManager* mSceneMgr;
	void makePlane(const Ogre::String name, const Ogre::String nodeName, Ogre::Vector3 transVector, Ogre::String texture);
	Ogre::Light* makeSpotlight(const Ogre::String name, Ogre::Vector3 transVector);
	Ogre::String getTexture(int x, int z);
	static const Ogre::String floorNames[5][5];
	static const Ogre::String floorNodeNames[5][5];
	static const Ogre::String spotlightNames[5][5];
	Ogre::Real timer;
	void updateLights();
	bool** spotlights;
};

#endif