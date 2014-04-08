#include "OgreApp1.h"

//-------------------------------------------------------------------------------------
OgreApp1::OgreApp1(void)
{
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
 
    Ogre::Entity* entPlayer = mSceneMgr->createEntity("Player", "ninja.mesh");
    entPlayer->setCastShadows(true);
	Ogre::SceneNode* nodPlayer = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodPlayer->attachObject(entPlayer);
	nodPlayer->translate(Ogre::Vector3(-400, 0, 400));

    Ogre::Entity* entOpponent = mSceneMgr->createEntity("Opponent", "penguin.mesh");
    entOpponent->setCastShadows(true);
    Ogre::SceneNode* nodOpponent = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodOpponent->attachObject(entOpponent);
	nodOpponent->translate(Ogre::Vector3(400, 25, -400));
 
	mSceneMgr->getRootSceneNode()->createChildSceneNode("floor");
	Ogre::String names[5][5] = {
		{"F11","F21","F31","F41","F51"},
	    {"F12","F22","F32","F42","F52"},
	    {"F13","F23","F33","F43","F53"},
	    {"F14","F24","F34","F44","F54"},
	    {"F15","F25","F35","F45","F55"}
	};
	for (int x=0; x<5; x++) {
		for (int z=0; z<5; z++) {
			Ogre::Vector3 transVector = Ogre::Vector3(200*x-400, 0, 200*z-400);
			makePlane(names[x][z], transVector);
		}
	}
 
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 0));
 
    pointLight->setDiffuseColour(1.0, 0.5, 0.5);
    pointLight->setSpecularColour(1.0, 0.5, 0.5);
}

void OgreApp1::makePlane(const Ogre::String name, Ogre::Vector3 transVector) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 200, 200, 2, 2, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entGround = mSceneMgr->createEntity(name, "ground");
    Ogre::SceneNode *floorPiece = mSceneMgr->getSceneNode("floor")->createChildSceneNode();
	floorPiece->translate(transVector);
	floorPiece->attachObject(entGround);
    entGround->setMaterialName("Examples/RustySteel");
    entGround->setCastShadows(false);
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
