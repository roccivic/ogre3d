#include "OgreApp1.h"


OgreApp1::OgreApp1(void) {
	timerForSquares = 0.5;
}
 
OgreApp1::~OgreApp1(void) {
}

void OgreApp1::createCamera(void) {
	// create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction  
    mCamera->setPosition(Ogre::Vector3(0,700,1300));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
 
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void OgreApp1::createViewports(void) {
	// Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight())); 
}

void OgreApp1::createScene(void) {
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 5000, false);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

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
	player = new Player(mSceneMgr);
	player->makePlayer();
}

void OgreApp1::createFrameListener(void) {
	BaseApplication::createFrameListener();
}

bool OgreApp1::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    bool ret = BaseApplication::frameRenderingQueued(evt);
	player->tick(evt);
	mDetailsPanel->setParamValue(0, "Ninja");
	mDetailsPanel->setParamValue(1, "Jaiqua");
	mDetailsPanel->setParamValue(2, "Robot");
	timerForSquares -= evt.timeSinceLastFrame;
	if (timerForSquares < 0) {
		timerForSquares = 0.5;
		floor->updateLights();
	}
    return ret;
}

// OIS::KeyListener
bool OgreApp1::keyPressed( const OIS::KeyEvent& evt ) {
    switch (evt.key) {
		case OIS::KC_UP:
		case OIS::KC_W:
			player->keyUp();
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:
			player->keyDown();
			break;
 
		case OIS::KC_LEFT:
		case OIS::KC_A:
			player->keyLeft();
			break;
 
		case OIS::KC_RIGHT:
		case OIS::KC_D:
			player->keyRight();
			break;

		default:
			break;
    }
    return true;
}

bool OgreApp1::keyReleased( const OIS::KeyEvent& evt ) {
	return true;
}

// OIS::MouseListener
bool OgreApp1::mouseMoved( const OIS::MouseEvent& evt ){
	return true;
}
bool OgreApp1::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id ){
	return true;
}
bool OgreApp1::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id ){
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
