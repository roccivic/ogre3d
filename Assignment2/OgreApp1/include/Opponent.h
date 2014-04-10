#include "BaseApplication.h"

class Opponent
{
public:
    Opponent(Ogre::SceneManager* mSceneMgr);
    ~Opponent();
	int* getPosition();
	void makeOpponent();
	void tick(const Ogre::FrameEvent& evt);

private:
	int position[2];
	Ogre::SceneManager* mSceneMgr;
	Ogre::AnimationState *mOpponentAnimation;
    Ogre::Entity *mOpponent;
    Ogre::SceneNode *mOpponentNode;
};