#include "BaseApplication.h"

class Floor
{
public:
    Floor(Ogre::SceneManager* mSceneMgr);
    ~Floor();
	void makeFloor();

private:
	Ogre::SceneManager* mSceneMgr;
	void makePlane(const Ogre::String name, Ogre::Vector3 transVector, Ogre::String texture);
	Ogre::Light* makeSpotlight(const Ogre::String name, Ogre::Vector3 transVector);
	Ogre::String getTexture(int x, int z);
};