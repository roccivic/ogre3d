#include "BaseApplication.h"

class Opponent
{
public:
    Opponent(Ogre::SceneManager* mSceneMgr);
    ~Opponent();
	void makeOpponent();
	void tick(const Ogre::FrameEvent& evt);

private:
	Ogre::SceneManager* mSceneMgr;
	Ogre::AnimationState *mOpponentAnimation;
    Ogre::Entity *mOpponent;
    Ogre::SceneNode *mOpponentNode;
};