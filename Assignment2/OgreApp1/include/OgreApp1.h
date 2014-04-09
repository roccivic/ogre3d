#ifndef __OgreApp1_h_
#define __OgreApp1_h_

#include "BaseApplication.h"
#include "Floor.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

class OgreApp1 : public BaseApplication
{
public:
    OgreApp1(void);
    virtual ~OgreApp1(void);

protected:
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
    virtual void createFrameListener(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
    bool processUnbufferedInput(const Ogre::FrameEvent& evt);

	Ogre::AnimationState *mPlayerAnimation;      // The current animation state of the object
    Ogre::Entity *mPlayer;                       // The Entity we are animating
    Ogre::SceneNode *mPlayerNode;                // The SceneNode that the Entity is attached to

	Ogre::Real timerForSquares;

	Floor* floor;
};

#endif // #ifndef __OgreApp1_h_
