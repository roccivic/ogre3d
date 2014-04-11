#ifndef __Floor_h_
#define __Floor_h_
#include "BaseApplication.h"

class Floor
{
public:
    Floor(Ogre::SceneManager* mSceneMgr);
    ~Floor();
	void makeFloor();
	void tick(const Ogre::FrameEvent& evt);

private:
	Ogre::SceneManager* mSceneMgr;
	void makePlane(const Ogre::String name, Ogre::Vector3 transVector, Ogre::String texture);
	Ogre::Light* makeSpotlight(const Ogre::String name, Ogre::Vector3 transVector);
	Ogre::String getTexture(int x, int z);
	static const Ogre::String floorNames[5][5];
	static const Ogre::String spotlightNames[5][5];
	Ogre::Real timer;
	void updateLights();
};

#endif