#ifndef __OgreApp1_h_
#define __OgreApp1_h_

#include "BaseApplication.h"
#include "Floor.h"
#include "Player.h"
#include "Opponent.h"
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
	// OIS::KeyListener
    virtual bool keyPressed(const OIS::KeyEvent& evt);
    virtual bool keyReleased(const OIS::KeyEvent& evt);
	// OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent& evt );
    virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
private:
	Floor* floor;
	Player* player;
	Opponent* opponent;
	bool panning;
	bool switchCamera;
    Ogre::Camera* mCamera2;
	Ogre::Viewport* vp;
};

#endif // #ifndef __OgreApp1_h_
