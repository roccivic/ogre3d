#ifndef __Opponent_h_
#define __Opponent_h_
#include "BaseApplication.h"
#include "Player.h"

class Opponent
{
public:
    Opponent(Ogre::SceneManager* mSceneMgr, Player* player);
    ~Opponent();
	int* getPosition();
	void makeOpponent();
	bool tick(const Ogre::FrameEvent& evt);
	void die();

private:
	Player* player;
	Ogre::Real timer;
	int position[2];
	Ogre::SceneManager* mSceneMgr;
	Ogre::AnimationState *mOpponentAnimation;
    Ogre::Entity *mOpponent;
    Ogre::SceneNode *mOpponentNode;
	void move();
	bool busy;
	Ogre::Real mDistance;
    Ogre::Vector3 mDirection;
    Ogre::Vector3 mDestination;
	void lookAtOrigin();

	Ogre::Quaternion mOrientSrc;
	Ogre::Quaternion mOrientDest;
	Ogre::Real mRotProgress;
	Ogre::Real mRotFactor;
	bool mRotating1;
	bool mRotating2;
	bool dying;
	Ogre::Real dyingProgress;
	void reset();
};

#endif