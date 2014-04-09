#include "OgreApp1.h"

//-------------------------------------------------------------------------------------
OgreApp1::OgreApp1(void)
{
	timerForSquares = 0.5;
}
 
//-------------------------------------------------------------------------------------
OgreApp1::~OgreApp1(void)
{
}
 
//-------------------------------------------------------------------------------------
void OgreApp1::createCamera(void)
{
	// create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction  
    mCamera->setPosition(Ogre::Vector3(0,700,1300));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
 
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
 
//-------------------------------------------------------------------------------------
void OgreApp1::createViewports(void)
{
	// Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight())); 
}
 
//-------------------------------------------------------------------------------------
void OgreApp1::createScene(void)
{
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 5000, false);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
 
    mPlayer = mSceneMgr->createEntity("Player", "ninja.mesh");
    mPlayer->setCastShadows(true);
	mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
	mPlayerNode->attachObject(mPlayer);
	mPlayerNode->translate(Ogre::Vector3(-400, 0, 400));

	Ogre::Light* spotLight = mSceneMgr->createLight("PlayerLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0.1, 1.0, 0.1);
    spotLight->setSpecularColour(0.1, 1.0, 0.1);
    spotLight->setDirection(0, -1, 0);
    spotLight->setPosition(Ogre::Vector3(0, 300, 0));
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(35));
	mPlayerNode->attachObject(spotLight);


    Ogre::Entity* entOpponent = mSceneMgr->createEntity("Opponent", "penguin.mesh");
    entOpponent->setCastShadows(true);
    Ogre::SceneNode* nodOpponent = mSceneMgr->getRootSceneNode()->createChildSceneNode("OpponentNode");
	nodOpponent->attachObject(entOpponent);
	nodOpponent->translate(Ogre::Vector3(400, 25, -400));
 

	Ogre::Light* spotLight2 = mSceneMgr->createLight("OpponentLight");
    spotLight2->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight2->setDiffuseColour(0.1, 0.1, 1.0);
    spotLight2->setSpecularColour(0.1, 0.1, 1.0);
    spotLight2->setDirection(0, -1, 0);
    spotLight2->setPosition(Ogre::Vector3(0, 300, 0));
    spotLight2->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(35));
	nodOpponent->attachObject(spotLight2);


	floor = new Floor(mSceneMgr);
	floor->makeFloor();
}

void OgreApp1::createFrameListener(void){
	BaseApplication::createFrameListener();
}

bool OgreApp1::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);

 	mPlayerAnimation = mPlayer->getAnimationState("Idle2");
    mPlayerAnimation->setLoop(true);
    mPlayerAnimation->setEnabled(true);

    if(!processUnbufferedInput(evt)) return false;

	mDetailsPanel->setParamValue(0, "Ninja");

	mPlayerAnimation->addTime(evt.timeSinceLastFrame);


	timerForSquares -= evt.timeSinceLastFrame;
	if (timerForSquares < 0) {
		timerForSquares = 0.5;
		floor->updateLights();
	}

    return ret;
}

bool OgreApp1::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    static Ogre::Real mRotate = 0.13;   // The rotate constant
    static Ogre::Real mMove = 250;      // The movement constant
	mKeyboard->capture();
	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
	bool moved = false;
	if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
	{
		transVector.z -= mMove;
		moved = true;
		mPlayerAnimation = mPlayer->getAnimationState("Walk");
        mPlayerAnimation->setLoop(true);
        mPlayerAnimation->setEnabled(true);
	}
	if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
	{
		transVector.z += mMove;
		moved = true;
		mPlayerAnimation = mPlayer->getAnimationState("Walk");
        mPlayerAnimation->setLoop(true);
        mPlayerAnimation->setEnabled(true);
	}
	if (moved) {
		if (mKeyboard->isKeyDown(OIS::KC_A)) // Left - yaw
		{
			// Yaw left
			mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(mRotate * 25));
		}
		if (mKeyboard->isKeyDown(OIS::KC_D)) // Right - yaw
		{
			// Yaw right
			mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-mRotate * 25));
		}
	}
	mSceneMgr->getSceneNode("PlayerNode")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
    return true;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        OgreApp1 app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
