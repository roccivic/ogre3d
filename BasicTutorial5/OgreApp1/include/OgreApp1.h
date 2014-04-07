#ifndef __BasicTutorial05_h_
#define __BasicTutorial05_h_
 
#include "BaseApplication.h"
 
class BasicTutorial05 : public BaseApplication
{
public:
    BasicTutorial05(void);
    virtual ~BasicTutorial05(void);
 
protected:
    virtual void createScene(void);
    virtual void createFrameListener(void);
 
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt );
    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent& evt );
    virtual bool keyReleased( const OIS::KeyEvent& evt );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent& evt );
    virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
 
    Ogre::Real mRotate;          // The rotate constant
    Ogre::Real mMove;            // The movement constant
    Ogre::SceneNode *mCamNode;   // The SceneNode the camera is currently attached to
    Ogre::Vector3 mDirection;    // Value to move in the correct direction
 
};
 
#endif // #ifndef __BasicTutorial05_h_