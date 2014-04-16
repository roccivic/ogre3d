#ifndef __Player_h_
#define __Player_h_
#include "BaseApplication.h"
#include "Direction.h"

class Player
{
public:
    Player(Ogre::SceneManager* mSceneMgr);
    ~Player();
	int* getPosition();
	void makePlayer();
	bool tick(const Ogre::FrameEvent& evt);
	void keyUp();
	void keyDown();
	void keyLeft();
	void keyRight();
	void character1();
	void character2();
	void character3();
	void die();
	bool isWalking();

private:
	int nextKey;
	int position[2];
	int direction;
	Ogre::SceneManager* mSceneMgr;
	Ogre::AnimationState *mPlayerAnimation1;
	Ogre::AnimationState *mPlayerAnimation2;
	Ogre::AnimationState *mPlayerAnimation3;
    Ogre::Entity *mPlayer1;
    Ogre::Entity *mPlayer2;
    Ogre::Entity *mPlayer3;
    Ogre::SceneNode *mPlayerNode;
	bool rotated;
	bool updatePosition(int dir);
	bool mRotating;
	bool mRotatingLeft;
	Ogre::Real mRotatingTarget;
	bool walking;
	Ogre::Real mDistance;
    Ogre::Vector3 mDirection;
    Ogre::Vector3 mDestination;
	bool dying;
	Ogre::Real dyingProgress;
	void reset();
};

#endif