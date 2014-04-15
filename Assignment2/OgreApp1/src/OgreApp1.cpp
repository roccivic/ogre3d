#include "OgreApp1.h"


OgreApp1::OgreApp1(void) {
	panning = false;
	switchCamera = false;
}
 
OgreApp1::~OgreApp1(void) {
}

void OgreApp1::createCamera(void) {
    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Ogre::Vector3(0,700,1300));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    mCamera2 = mSceneMgr->createCamera("PlayerCam2");
    mCamera2->setPosition(Ogre::Vector3(0,300,400));
    mCamera2->lookAt(Ogre::Vector3(0,0,-400));
    mCamera2->setNearClipDistance(5);
}

void OgreApp1::createViewports(void) {
    vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	mCamera2->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void OgreApp1::createScene(void) {
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 5000, false);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	floor = new Floor(mSceneMgr);
	floor->makeFloor();
	player = new Player(mSceneMgr);
	player->makePlayer();
	mSceneMgr->getSceneNode("PlayerNode")->attachObject(mCamera2);
	opponent = new Opponent(mSceneMgr, player);
	opponent->makeOpponent();
}

void OgreApp1::createFrameListener(void) {
	BaseApplication::createFrameListener();
}

bool OgreApp1::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    bool ret = BaseApplication::frameRenderingQueued(evt);
	player->tick(evt);
	opponent->tick(evt);
	floor->tick(evt);
	mDetailsPanel->setParamValue(0, "Ninja");
	mDetailsPanel->setParamValue(1, "Jaiqua");
	mDetailsPanel->setParamValue(2, "Robot");
	mDetailsPanel->setParamValue(3, "Change camera");
    return ret;
}

// OIS::KeyListener
bool OgreApp1::keyPressed(const OIS::KeyEvent& evt) {
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
		case OIS::KC_1:
			player->character1();
			break;
		case OIS::KC_2:
			player->character2();
			break;
		case OIS::KC_3:
			player->character3();
			break;
		case OIS::KC_C:
			switchCamera = ! switchCamera;
			if (switchCamera) {
				vp->setCamera(mCamera2);
			} else {
				vp->setCamera(mCamera);
			}
			break;
		default:
			break;
    }
    return true;
}

bool OgreApp1::keyReleased(const OIS::KeyEvent& evt) {
	return true;
}

// OIS::MouseListener
bool OgreApp1::mouseMoved(const OIS::MouseEvent& evt) {
	bool retval = true;
	if (panning && ! switchCamera) {
		retval = BaseApplication::mouseMoved(evt);
	}
	return retval;
}
bool OgreApp1::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
	panning = true;
	return true;
}
bool OgreApp1::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
	panning = false;
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
